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

void encoder::init(int pin1, int pin2, int interrupt_number)
{
    if (interrupt_number == 0)
    {
        EICRA |= ((1 << ISC01) | ((1 << ISC00))); //Set interrupt 0 to trigger on the rising edge

        EIMSK |= (1 << INT0); //Enable interrupt 0
    }
    else if (interrupt_number == 1)
    {
        EICRA |= ((1 << ISC11) | ((1 << ISC10))); //Set interrupt 1 to trigger on the rising edge

        EIMSK |= (1 << INT1); //Enable interrupt 1
    }
    else
    {
        // Here is an error
    }
    DDRD &= ~((1 << PIN2) | (1 << PIN3)); //Set pins which the interrupts are mapped onto as inputs.
    PORTD |= ((1 << PIN2) | (1 << PIN3)); //Enable pull up resistors

    // Here below is are the pins output for controlling of the motor.
    DDRB |= ((1 << pin1) | (1 << pin2));  // Set pins
    DRV_PIN1 = pin1;
    DRV_PIN2 = pin2;
}

void encoder::turn_on()
{
    PORTB &= ~(1 << DRV_PIN1);

    PORTB |= (1 << DRV_PIN2);
    tau = micros();
}

void encoder::turn_off()
{
    PORTB &= ~((1 << DRV_PIN1) | (1 << DRV_PIN2)); // all pins to high except pins for high values.
    measurement = false;
}

void encoder::change_dir()
{
    PORTB = PORTB ^ ((1 << DRV_PIN1) | (1 << DRV_PIN2));
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
    int current_PPS = PPS[head];
    if (current_PPS < 100 && current_PPS > -100)
    {
        return 0;
    }
    else
    {
        return cum_sum / (N - 1);
    }
}

void encoder::calc_speed_micros(uint16_t time_micros)
{
    uint16_t micros = time_micros - old_time_micros;
    old_time_micros = time_micros;
    int current_PPS = 1000000 / micros;

    if (current_PPS >= 794 && !measurement) //794 is 63% of 1260
    {
        tau = time_micros - tau;
        measurement = true;
    }

    if (!(PIND & (1 << PIN3)))
    {
        current_PPS = -current_PPS;
    }

    if (head >= (N - 1))
    {
        head = 0;
    }
    else
    {
        head++;
    }

    PPS[head] = current_PPS;
    if (head == (N - 1))
    {
        cum_sum = cum_sum + current_PPS;
        cum_sum = cum_sum - PPS[0];
    }
    else
    {
        cum_sum = cum_sum + current_PPS;
        cum_sum = cum_sum - PPS[head + 1];
    }
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
