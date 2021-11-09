//
// Created by jon on 9/16/21.
// Motor controller sate
//
#include "State.h"
#include "states/Initialization.h"
#include "states/Operational.h"
#include "states/Stopped.h"
#include "avr/interrupt.h"
#include "main.h"


#define ARDUINO_1

constexpr double error_threshold = 0.05;
const uint16_t period_ms = 10;
const double Kp = 0.7875, Ki = 4.46; // If K_p is = 2.0 and reference speed to 1000, the output oscillates
double reference = 500;

// Ki = Kp/Ti

timer_8bit timer0(10);
Digital_in motorFault(1);
Context *context;

encoder motor(PIN2, PIN3, period_ms, 0);
Digital_out LED_TEST(4); //Digital is for C-register
// P_controller speed_controller(Kp, error_threshold);

constexpr int16_t max_val = 1200;
constexpr int16_t min_val = -1200;

#ifdef USE_P_CONTROLLER
p_controller speed_controller(Kp, -1200, 1200);
#else
pi_controller speed_controller(Kp, Ki, min_val, max_val, static_cast<double>(period_ms / 1000.0));
#endif

Digital_out led(5), driver_pin2(motor.getDRV_PIN2());

/*-------------CAN arrs---------------------------*/

constexpr uint8_t CAN_READ = 3;
constexpr uint8_t CAN_WRITE = 6;
constexpr uint8_t MSG_LEN = 8;


#ifdef ARDUINO_1
constexpr uint8_t MOTOR_ADDR = 0x01;
#else
constexpr uint8_t MOTOR_ADDR = 0x02;
#endif 
/*--------------Function prototypes--------------------*/

uint16_t modRTU_CRC(uint8_t buf[], int len);
void parseMessage(uint8_t* arr, uint8_t length);
uint8_t val_write(uint16_t address, int16_t value);
int16_t val_read(uint16_t address);

ISR(TIMER1_COMPA_vect)
{
    // driver_pin2.set_hi();
    PORTB |= (1 << motor.getDRV_PIN2());
}

ISR(TIMER1_COMPB_vect)
{
    PORTB &= ~(1 << motor.getDRV_PIN2());
}
uint16_t counter = 0;

ISR(TIMER0_COMPA_vect)
{
    counter++;
    if (counter >= timer0.getCounter())
    {
        led.toggle();
        counter = 0;
    }
}

ISR(INT0_vect)
{
    motor.calc_speed_micros(micros());
    if (motor.get_pulse_counter() > 700 || motor.get_pulse_counter() < -700)
    {
        motor.set_pulse_counter(0);
    }
}

void setup()
{

    Serial.begin(115200);

    context = new Context(new Initialization);
}

uint16_t command = 0x0042;
uint8_t RPI_msg[MSG_LEN] = {0, 0, 0, 0, 0, 0, 0, 0};

void loop()
{
    

    while (command == 0x0042)
    {

        context->Request1(0x00FF);

        if (Serial.available())
        {
            Serial.readBytes(RPI_msg, MSG_LEN);
            parseMessage(RPI_msg, MSG_LEN);
        }
        if (motorFault.is_hi())
        {
            command = 0x0002;
        }
    }
    if (command != 0x0042)
    {
        context->Request1(command);
        command = 0x0042;
        RPI_msg[0] = 0xFF;
    }

    while (motorFault.is_hi())
    {
        Serial.read(); // Keep serial from placing in buffer. Any commands entered here should be discarded.
    }
    delay(500);
}


void parseMessage(uint8_t* arr, uint8_t length) {
    
    uint8_t buffer[length];
    uint8_t error;
    if (arr[0] == MOTOR_ADDR)
    {
        
        uint16_t CRC = ((uint16_t)arr[length - 2] << 8) | arr[length - 1]; // Combining the two bytes to a single 16 bit number.
        if (CRC == modRTU_CRC(arr, length))
        {
            
            uint8_t function_code = arr[1];
            uint16_t mem_address = (uint16_t) ((arr[2] << 8) | arr[3]); // Combining the two bytes to a single 16 bit number.
            int16_t msg_value = (int16_t) ((arr[4] << 8) | arr[5]);   // Combining the two bytes to a single 16 bit number.
            uint16_t val_send, CRC_send; 
            
            switch (function_code)
            {
            case 0x03:
                val_send = val_read(mem_address);
                buffer[0] = arr[0];
                buffer[1] = arr[1];
                buffer[2] = arr[2];
                buffer[3] = arr[3];
                buffer[4] = (uint8_t)((val_send >> 8) & 0xFF);
                buffer[5] = (uint8_t)((val_send >> 0) & 0xFF);
                CRC_send = modRTU_CRC(buffer, length);
                buffer[6] = (uint8_t)((CRC_send >> 8) & 0xFF);
                buffer[7] = (uint8_t)((CRC_send >> 0) & 0xFF);
                Serial.write((char *)buffer,length);

                break;

            case 0x06:
                error = val_write(mem_address, msg_value);
                if(!error){
                    buffer[0] = arr[0];
                    buffer[1] = arr[1];
                    buffer[2] = arr[2];
                    buffer[3] = arr[3];
                    buffer[4] = arr[4];
                    buffer[5] = arr[5];
                    buffer[6] = arr[6];
                    buffer[7] = arr[7];
                    Serial.write((char *) buffer, length);
                
                } else {
                    buffer[0] = arr[0];
                    buffer[1] = (arr[1] | error<<8);
                    buffer[3] = 0x00;
                    buffer[4] = 0x00;
                    buffer[5] = 0x00;
                    buffer[6] = arr[6];
                    buffer[7] = arr[7];
                    Serial.write((char *)buffer, length);
                }
                break;
                
            default:
                buffer[0] = arr[0];
                buffer[1] = (arr[1] | 1<<8);
                Serial.write((char *)buffer, length);
                break;
            }
        }
    }

}

int16_t val_read(uint16_t address)
{
    switch (address)
    {
    case 1:
        return motor.get_average();
    default:
        return 2;
    }
}

uint8_t val_write(uint16_t address, int16_t value)
{
    uint8_t error;
    switch (address)
    {
    case 0:
        error = context->Request1(value);
        if(!error){
            return 0;
        } else {
            return error;
        }
    case 1:
        if(value < max_val || value > min_val){
            reference = static_cast<double>(value);
            return 0;
        } else {
            return 3;
        }
    
    default:
        return 2;
    }
}


//Cyclic redundancy check
uint16_t modRTU_CRC(uint8_t buf[], int len)
{
    uint16_t crc = 0xFFFF;
    for (int pos = 0; pos < (len-2); pos++)
    {
        crc ^= (uint16_t)buf[pos];

        for (int k = 8; k != 0; k--)
        {
            if ((crc & 0x0001) != 0)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
                crc >>= 1;
        }
    }
    return crc;
}
