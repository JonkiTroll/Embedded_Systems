//
// Created by jon on 9/15/21.
//
#include "encoder.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include <stdlib.h>

encoder::encoder() {

    count = 0;
    head = 0;

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

int encoder::calculate_average() {
    int sum = 0;

    for(int i = 0; i < 5; i++) {
        sum = sum + PPS[i];
    }
    return sum/5;
}

void encoder::calc_speed_micros(uint16_t time_micros)
{
    uint16_t micros = time_micros - old_time_micros;
    old_time_micros = time_micros;
    int current_PPS = 1000000/micros;

    if (!(PIND & (1 << PIN3)))
    {
        current_PPS = -current_PPS;
    }

    PPS[head] = current_PPS;

    if(head == 4){
        head = 0;
    }

    head++;
}

int encoder::getPPS()
{
    int current_PPS = PPS[head];

    if (current_PPS < 100 && current_PPS > -100)
    {
        current_PPS = 0;
    }

    return current_PPS;
}

