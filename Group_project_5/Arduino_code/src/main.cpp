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

/*-------------CAN messages---------------------------*/

constexpr uint8_t CAN_READ = 0x03;
constexpr uint8_t CAN_WRITE = 0x06;

#ifdef ARDUINO_1
constexpr uint8_t MOTOR_ADDR = 0x01;
#else
constexpr uint8_t MOTOR_ADDR = 0x02;
#endif
/*--------------Function prototypes--------------------*/

uint16_t modRTU_CRC(uint8_t buf[], int len);


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

uint8_t parseMessage(char arr[], int length);

void setup(){

    Serial.begin(115200);

    context = new Context(new Initialization);
}

char command = '0';

void loop(){

    while (command == '0') {

        context->Request1('l');

        if (Serial.available())
            command = Serial.read();

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

uint8_t parseMessage(char arr[], int length) {
    
    if(arr[0] == MOTOR_ADDR){

        if(arr[1] == CAN_READ) {

        } else if (arr[1] == CAN_WRITE){

        } else {
            
        }

    } else {

    }

    return 0;
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
