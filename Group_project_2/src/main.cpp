//
// Created by group 2 on 15/09/21.
//
//

#include "Arduino.h"
#include <util/delay.h>
#include "timer_ms.h"

#include <avr/interrupt.h>
#include "encoder.h"

#define TIMER_INTERVAL 1000

encoder motor;
double speed;

/*
timer_ms timer1(TIMER_INTERVAL);

ISR(TIMER1_COMPA_vect) {

}

ISR(TIMER1_COMPB_vect) {

}
*/
ISR(INT0_vect)
{
    motor.calc_speed_micros(micros());
}

void setup()
{

    //Serial.begin(115200);
    Serial.begin(9600); //Nano speed
    motor.init(PIN2, PIN3, 0);

    sei(); //Enable global interrupts
}

void loop()
{
    //_delay_ms(250);
    //speed = motor.calculate_speed();
    //Serial.print("pulses per second: ");
    //Serial.print(motor.getPPS());
    //Serial.print("\n\r");
    //Serial.print("average pulses per second: ");
    //Serial.println(motor.calculate_average());
    
    //Serial.print("\n\r");
    // 1250 - 1288 (1295)
    motor.turn_on();
    _delay_ms(100);
    Serial.println(motor.tau);
    _delay_ms(250);
    motor.turn_off();
    _delay_ms(1000);
}

/*
 *  ARDUINO Format:
 *
 *  int main(){
 *      setup();
 *
 *      while(1){
 *          //Serial check
 *          loop();
 *      }
 *      return 0;
 *  }
 */
