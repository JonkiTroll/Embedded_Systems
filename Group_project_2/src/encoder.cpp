//
// Created by jon on 9/15/21.
//
#include "encoder.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include <stdlib.h>
#include <Arduino.h>

//#define DEBUG

encoder::encoder()
{

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
    curr_time = micros();
#ifdef DEBUG
    Serial.print("start: ");
    Serial.println(curr_time);
#endif
}

void encoder::turn_off()
{
    PORTB &= ~((1 << DRV_PIN1) | (1 << DRV_PIN2)); // all pins to high except pins for high values.
    measurement = false;
}

void encoder::calc_speed_micros(uint32_t time_micros)
{
    uint16_t micros = time_micros - old_time_micros;
    old_time_micros = time_micros;
    int current_PPS = 1000000 / micros;

    if (current_PPS >= 800 && !measurement) //800 is 63% of 1266
    {
        #ifdef DEBUG
        Serial.print("end: ");
        Serial.println(time_micros);
        Serial.print("tau: ");
        Serial.println(tau);
        #endif
        tau = time_micros - curr_time;
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

int encoder::getPPS() const
{
    int current_PPS = PPS[head];

    if (current_PPS < 100 && current_PPS > -100)
    {
        return 0;
    }

    return current_PPS;
}

uint32_t encoder::getTau() const {
    return tau;
}
