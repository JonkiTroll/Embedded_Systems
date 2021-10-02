//
// Created by jon on 9/15/21.
//
#include "encoder.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include <stdlib.h>
#include <Arduino.h>

//#define DEBUG

/*
 * Initialize both the interrupts and GPIO pins used to control the motor. The GPIO pins are on PORTB.
 */
void encoder::init(int interrupt_number)
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
    DDRB |= ((1 << DRV_PIN1) | (1 << DRV_PIN2));  // Set pins

    timer1.init();
}

/*
 * Turns the DC motor on by setting the driver pin logic according to datasheet (DRV8833).
 */

void encoder::turn_on()
{

    PORTB &= ~(1 << DRV_PIN1);

    PORTB |= (1 << DRV_PIN2);
    curr_time = micros();
#ifdef DEBUG
    Serial.print("start: ");
    Serial.println(curr_time);
#endif
    timer1.enable();
}

/*
 * Turn the DC motor off by clearing the output.
 */

void encoder::turn_off()
{
    PORTB &= ~((1 << DRV_PIN1) | (1 << DRV_PIN2)); // all pins to high except pins for high values.
    timer1.disable();
    measurement = false; //Signal to the program that the time constant can be measured again
}

/*
 * Calculates the pulses per seconds as well as the average over 10 values. Does so by taking in the currently elapsed
 * time in micro seconds and subtracts it from the last time the function was called and converts to seconds to get the
 * frequency. This function should be placed in an interrupt service routine where an interrupt is called at either the
 * rising or falling edge of the pulse count.
 */

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

    //determine the direction of the motor.
    if (!(PIND & (1 << PIN3)))
    {
        current_PPS = -current_PPS;
        pulse_counter--;
    } else {
        pulse_counter++;
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

    //Calculate the cumulative sum for the average output
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

/*
 * Updates the duty cycle of the PWM signal. The PWM output is linear in that top speed equals 100% duty cycle,
 * and minimum speed equals 0% duty cycle.
 */

void encoder::update_speed(int32_t new_speed){

    /*
    if(new_speed < 0) {
        isGoingForward = false;
        new_speed = -new_speed;

    }   else {
        isGoingForward = true;
    }
    */

    //keeps the output within set limits.
    if ( new_speed > 1200) {
        new_speed =  1200;
    } else if (new_speed < 100) {
        new_speed = 100;
    }
    //calculate duty cycle as a percentage.
    auto dutyCycle = static_cast<uint16_t>(100*new_speed/top_speed);

#ifdef DEBUG
    Serial.print("Dutycycle: ");
    Serial.println(dutyCycle);
#endif
    //Update the duty cycle of the timer
    timer1.setDutyCycle(dutyCycle);
}

/*
 * Calculates the average value of the speed. cum_sum is the cumulative sum which is calculated in the
 * calc_speed_micros() function.
 */

int16_t encoder::get_average() const{
    int16_t result = cum_sum/(N-1);
    return result;
}

/*
 * Returns the most recently calculated Pulses per second.
 */

uint16_t encoder::getPPS() const
{
    int current_PPS = PPS[head];

    if (current_PPS < 100 && current_PPS > -100)
    {
        return 0;
    }

    return current_PPS;
}
/*
 * Returns the most recently measured time constant
 */
uint32_t encoder::get_tau() const {
    return tau;
}
/*
 * getter for the driver pin1.
 */
uint8_t encoder::getDRV_PIN1() const{
    return DRV_PIN1;
}
/*
 * getter for the driver pin2.
 */
uint8_t encoder::getDRV_PIN2() const{
    return DRV_PIN2;
}
/*
 * returns pulse counter
 */

int16_t encoder::get_pulse_counter() const {
    return pulse_counter;
}
/*
 * Sets the pulse counter to a new value
 */
void encoder::set_pulse_counter(int16_t new_value) {
    pulse_counter = new_value;
}
/*
 * returns the direction in which the motor is going. CURRENTLY NOT IMPLEMENTED!
 */
bool encoder::is_going_forward() const {
    return isGoingForward;
}