//
// Created by jon on 9/15/21.
//
#include "encoder.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include <stdlib.h>

encoder::encoder() {

    count = 0;

}

/*
 * Update the pulse ocunt. Should be called via external ISR to PIN2.
 */

void encoder::update_count(){

    if (!(PIND & (1 << PIN3)))
        count++;
    else
        count--;


    if(abs(count) > PPR){
        count = 0;
    }
}
/*
 * Calculate the speed of the motor in pulses per revolution. This is per revolution of the wheel, not the motor axle.
 */
double encoder::calculate_speed() {

        int32_t old_count = count;
        static int32_t speed;

        _delay_ms(100); //Currently just polls. Would prefer to set a single shot timer.

        if(abs(count) >= abs(old_count)) {
            speed = (count - old_count) * 10;
        } else {
            speed = (count - (old_count + PPR)) * 10; //Only works in positive direction. should be -PPR for negative
        }
        return speed;
}

void encoder::calc_speed_micros(uint16_t time_micros)
{
    uint16_t micros = time_micros - old_time_micros;
    old_time_micros = time_micros;

    PPS =  1000000/micros;
    if (!(PIND & (1 << PIN3)))
    {
        PPS = -PPS;
    }
}

int encoder::getPPS()
{
    if (PPS < 100 && PPS > -100)
    {
        PPS = 0;
    }

    return PPS;
}
