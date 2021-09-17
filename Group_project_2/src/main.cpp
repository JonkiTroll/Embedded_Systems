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
ISR(INT0_vect) {
    motor.calc_speed_micros(micros());
}



void setup(){

    //Serial.begin(115200);
    Serial.begin(9600); //Nano speed

    EICRA |= ((1 << ISC01) | ((1 << ISC00)));   //Set interrupt 0 to trigger on the rising edge

    EIMSK |= (1 << INT0);       //Enable interrupt 0 and 1

    DDRD &= ~((1 << DDD3) | (1 << DDD2));       //Set pins which the interrupt  s are mapped onto as inputs.

    PORTD |= ((1 << PIN2) | (1 << PIN3));

    PORTD |= ((1 << PIN2) | (1 << PIN3));       //Enable pull up resistors

    sei();                                    //Enable global interrupts

}

void loop(){
    _delay_ms(2000);
    //speed = motor.calculate_speed();
    Serial.print("pulses per second: ");
    Serial.println(motor.getPPS());
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
