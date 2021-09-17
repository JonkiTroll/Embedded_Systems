//
// Created by jon on 9/15/21.
//
#include "encoder.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include <stdlib.h>
#include <Arduino.h>

encoder::encoder()
{

    count = 0;
    head = 0;
}

/*
 * Update the pulse ocunt. Should be called via external ISR to PIN2.
 */

void encoder::update_count()
{

    if (!(PIND & (1 << PIN3)))
        count++;
    else
        count--;

    if (abs(count) > PPR)
    {
        count = 0;
    }
}
/*
 * Calculate the speed of the motor in pulses per revolution. This is per revolution of the wheel, not the motor axle.
 */
double encoder::calculate_speed()
{

    int32_t old_count = count;
    static int32_t speed;

    _delay_ms(100); //Currently just polls. Would prefer to set a single shot timer.

    if (abs(count) >= abs(old_count))
    {
        speed = (count - old_count) * 10;
    }
    else
    {
        speed = (count - (old_count + PPR)) * 10; //Only works in positive direction. should be -PPR for negative
    }
    return speed;
}

int encoder::calculate_average()
{
    //int16_t sum = 0;

    //for (int i = 0; i < N; i++)
    //{
    //    sum = sum + PPS[i];
    //}
    //return sum / N;
    int current_PPS = 0;
    if (head == 0)
    {
        current_PPS = PPS[N - 1];
    }
    else
    {
        current_PPS = PPS[head - 1];
    }

    if (current_PPS < 100 && current_PPS > -100)
    {
        return 0;
    }
    else
    {
        return cum_sum / N;
    }
}

void encoder::calc_speed_micros(uint16_t time_micros)
{
    uint16_t micros = time_micros - old_time_micros;
    old_time_micros = time_micros;
    int current_PPS = 1000000 / micros;

    if (!(PIND & (1 << PIN3)))
    {
        current_PPS = -current_PPS;
    }

    PPS[head] = current_PPS;
    if (head == 0)
    {
        cum_sum = cum_sum + current_PPS - PPS[N - 1];
    }
    else
    {
        cum_sum = cum_sum + current_PPS - PPS[head - 1];
    }
    if (head == (N - 1))
    {
        head = 0;
    }

    head++;
}

int encoder::getPPS()
{
    int current_PPS = PPS[head];

    if (current_PPS < 100 && current_PPS > -100)
    {
        return 0;
    }

    return current_PPS;
}
