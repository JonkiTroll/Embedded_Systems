//
// Created by jon on 8/18/21.
//
#include <util/delay.h>
#include "digital_in.h"
#include "digital_out.h"

#include <avr/interrupt.h>

Digital_out led(5);
bool flag = false;
int counter = 0;

ISR(INT0_vect){
    if(!flag){
        flag = true;
        counter++;
        led.set_hi();
    }
}

ISR(INT1_vect){
    if(!flag){
        flag = true;
        counter--;
        led.set_lo();
    }
}

int main() {

    EICRA |= (1<<ISC11);

    EIMSK |= ((1 << INT0) | (1<<INT1));

    DDRD &= ~((1 << DDD2) | (1 << DDD1));

    PORTB |= ((1 << PIN2) | (1 << PIN1));

    sei();

    while(true){
        if(!(PIND & (1<<PIN1)) && !(PIND & (1 << PIN2))){
            flag = false;
        }
    }



    /*
    Digital_in encoderA(0);
    Digital_in encoderB(1);
    Digital_out led(5);

    int8_t increment = 0;
    bool flag = false;

    encoderA.init();
    encoderB.init();
    led.init();

    while(true){

        if(encoderA.is_hi() && !flag){
            increment++;
            flag = true;
            led.set_hi();
        } else if (encoderB.is_hi() && !flag) {
            increment--;
            flag = true;
            led.set_hi();
        } else if (encoderA.is_lo() && encoderB.is_lo()) {
            flag = false;
            led.set_lo();
        }

    }
*/

    return 0;

}



//static_assert((pin >= 0 && pin <=13), "Invalid pin! choose between 0 and 13!"); //Compile time assert!! Doesn't work in the class though.