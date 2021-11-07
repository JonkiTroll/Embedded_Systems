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

constexpr double error_threshold = 0.05;
const uint16_t period_ms = 10;
const double Kp = 0.7875, Ki = 4.46; //If K_p is = 2.0 and reference speed to 1000, the output oscillates
double reference = 1000;

//Ki = Kp/Ti

timer_8bit timer0(10);
Digital_in motorFault(1);
Context *context;
encoder motor(PIN2, PIN3, period_ms, 0);
//P_controller speed_controller(Kp, error_threshold);

#ifdef USE_P_CONTROLLER
p_controller speed_controller(Kp, -1200, 1200);
#else
pi_controller speed_controller(Kp, Ki, -1200, 1200, static_cast<double>(period_ms/1000.0));
#endif

Digital_out led(5), driver_pin2(motor.getDRV_PIN2());

/*-------------CAN arrs---------------------------*/

constexpr uint8_t CAN_READ = 0x03;
constexpr uint8_t CAN_WRITE = 0x06;
constexpr uint8_t MSG_LEN = 32;

#ifdef ARDUINO_1
constexpr uint8_t MOTOR_ADDR = 0x01;
#else
constexpr uint8_t MOTOR_ADDR = 0x02;
#endif 
/*--------------Function prototypes--------------------*/

uint16_t modRTU_CRC(uint8_t buf[], int len);
void parseMessage(char arr[], int length);
void val_write(uint16_t address, int16_t value);
int16_t val_read(uint16_t address);

ISR(TIMER1_COMPA_vect) {
    //driver_pin2.set_hi();
    PORTB |= (1<<motor.getDRV_PIN2());
}

ISR(TIMER1_COMPB_vect) {
    PORTB &= ~(1<<motor.getDRV_PIN2());
}
uint16_t counter = 0;

ISR(TIMER0_COMPA_vect) {
    counter++;
    if(counter>=timer0.getCounter()){
            led.toggle();
            counter = 0;
        }
}

ISR(INT0_vect) {
    motor.calc_speed_micros(micros());
    if (motor.get_pulse_counter() > 700 || motor.get_pulse_counter() < -700) {
        motor.set_pulse_counter(0);
    }
}


void setup(){

    Serial.begin(115200);

    context = new Context(new Initialization);
}



void loop(){

    char RPI_msg[MSG_LEN];
    char command = '0';

    while (command = '0') {

        context->Request1('l');

        if (Serial.available()){
            Serial.readBytes(RPI_msg, MSG_LEN);
            parseMessage(RPI_msg, MSG_LEN);
        }
        if(motorFault.is_hi()) {
            command = 0x02;
         }


    }
    if (command != '0') {
        context->Request1(command);
        command = '0';
    }

    while(motorFault.is_hi()) {
        Serial.read(); //Keep serial from placing in buffer. Any commands entered here should be discarded.
    }
    delay(500);

}


void parseMessage(char arr[], int length) {
    
    uint8_t buffer[MSG_LEN];

    if(arr[0] == MOTOR_ADDR){
        
        uint8_t function_code = arr[1];
        uint16_t mem_address = ((uint16_t)arr[2] << 8) | arr[3]; // Combining the two bytes to a single 16 bit number.
        uint16_t msg_value = ((uint16_t) arr[4] << 8) | arr[5];   // Combining the two bytes to a single 16 bit number.
        switch (function_code){
            case CAN_READ:
                uint16_t val_send = val_read(mem_address);
                buffer[0] = arr[0];
                buffer[1] = arr[1];
                buffer[2] = arr[2];
                buffer[3] = arr[3];
                buffer[4] = (uint8_t)((val_send >> 8) & 0xFF);
                buffer[5] = (uint8_t)((val_send >> 0) & 0xFF);
                uint16_t CRC_send = 0x4545;//modRTU_CRC(buffer, MSG_LEN);
                buffer[6] = (uint8_t)((CRC_send >> 8) & 0xFF);
                buffer[7] = (uint8_t)((CRC_send >> 0) & 0xFF);
                Serial.print((char*)buffer);
          
            break;
            
            case CAN_WRITE:
                buffer[0] = arr[0];
                buffer[1] = arr[1];
                buffer[2] = arr[2];
                buffer[3] = arr[3];
                buffer[4] = arr[4];
                buffer[5] = arr[5];
                buffer[6] = arr[6];
                buffer[7] = arr[7];
                Serial.write((char*)buffer,MSG_LEN);
                val_write(mem_address, msg_value);
                break;
            default:
                break;
        }


    }

}

int16_t val_read(uint16_t address){
    switch (address) {
        case 1:
            return motor.get_average();
        case 2:
            return static_cast<int16_t>(speed_controller.getProportionalGain());
        case 3:
            return static_cast<int16_t>(speed_controller.getIntegralGain());
        default:
            return 0xFFFF;
        
    }
}

void val_write(uint16_t address, int16_t value){
    switch(address) {
        case 0:
            context->Request1(static_cast<uint8_t>(value));
            break;
        case 1:
            reference = static_cast<double>(value);
            break;
        case 2:
            speed_controller.setProportionalGain(static_cast<double>(value));
            break;
        case 3:
            speed_controller.setIntegralGain(static_cast<double>(value));
        default:
            break;

    }
}


uint16_t modRTU_CRC(uint8_t buf[], int len)
{
  uint16_t crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++)
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
