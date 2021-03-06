//
// Created by group on 8/18/21.
//
//
#include <util/delay.h>
#include "digital_in.h"
#include "digital_out.h"

#include <avr/interrupt.h>

Digital_out led(5);
bool flag = false;
int counter = 0;

void reset() {
    flag = false;
    led.set_lo();
}

ISR(INT1_vect) {
    if (!flag) {
        counter--;
        led.set_hi();
        flag = true;
    }
}

ISR(INT0_vect) {
    if (!flag) {
        counter++;
        led.set_hi();
        flag = true;
    }
}

int main() {

    EICRA |= ((1 << ISC11) | ((1 << ISC10)));   //Set interrupt 1 to trigger on the rising edge
    EICRA |= ((1 << ISC01) | ((1 << ISC00)));   //Set interrupt 0 to trigger on the rising edge

    EIMSK |= ((1 << INT0) | (1 << INT1));       //Enable interrupt 0 and 1

    DDRD &= ~((1 << DDD3) | (1 << DDD2));       //Set pins which the interrupts are mapped onto as inputs.

    PORTD |= ((1 << PIN2) | (1 << PIN3));       //Enable pull up resistors

    led.init();                                 //Initialize led
    sei();                                      //Enable global interrupts

    while (true) {
        if ((PIND & (1 << PIN3)) && (PIND & (1 << PIN2))) {
            _delay_us(10);
            reset();
        }
    }



    return 0;

}



//static_assert((pin >= 0 && pin <=13), "Invalid pin! choose between 0 and 13!"); //Compile time assert!! Doesn't work in the class though.