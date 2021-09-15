//
// Created by group on 8/18/21.
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
    motor.update_count();
}



void setup(){

    Serial.begin(115200);

    EICRA |= ((1 << ISC01) | ((1 << ISC00)));   //Set interrupt 0 to trigger on the rising edge

    EIMSK |= (1 << INT0);       //Enable interrupt 0 and 1

    DDRD &= ~((1 << DDD3) | (1 << DDD2));       //Set pins which the interrupt  s are mapped onto as inputs.

    PORTD |= ((1 << PIN2) | (1 << PIN3));

    PORTD |= ((1 << PIN2) | (1 << PIN3));       //Enable pull up resistors

    sei();                                    //Enable global interrupts

}

void loop(){
    _delay_ms(2000);
    speed = motor.calculate_speed();
    Serial.print("pulses per second: ");
    Serial.println(speed);
}

/*
 *  ARDUINO Format:
 *
 *  int main(){
 *      setup();
 *
 *      while(1){
 *          loop();
 *      }
 *      return 0;
 *  }
 */
