//
// Created by jon on 8/30/21.
// Implementation of a millisecond timer for the Arduino UNO using the AVR toolchain.
//

#include "timer_ms.h"

/*
 * constructor. If duty cycle is not declared, a default value of 50 is gicen.
 */
timer_ms::timer_ms(uint16_t intervalMs) : mTimerInterval(intervalMs), mDutyCycle(50) {

    if(intervalMs != 0) {
        TCCR1A = 0; //Clear Timer register A
        TCCR1B = 0; //Clear Timer register B
        TCNT1 = 0;  //Clear counter


        OCR1A = ((160 * 100) / 1024) * mTimerInterval - 1;           //Set the A compare register
        OCR1B = ((160 * mDutyCycle) / 1024) * mTimerInterval - 1;    //Set the B compare register
        TCCR1B |= (1 << WGM12);                                 //configure the counter to clear when OCR1A is called
        TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);                  //Enable interrupts
        TCCR1B |= (1 << CS12) | (1 << CS10);                    //Configure prescaler (prescaler = 1024)
    }
};

timer_ms::timer_ms(uint16_t intervalMs, uint16_t dutyCycle) : mTimerInterval(intervalMs), mDutyCycle(dutyCycle) {

    if(intervalMs != 0) {
        TCCR1A = 0; //Clear Timer register A
        TCCR1B = 0; //Clear Timer register B
        TCNT1 = 0;  //Clear counter


        OCR1A = ((160 * 100) / 1024) * mTimerInterval - 1;           //Set the A compare register
        OCR1B = ((160 * mDutyCycle) / 1024) * mTimerInterval - 1;    //Set the B compare register
        TCCR1B |= (1 << WGM12);                                 //configure the counter to clear when OCR1A is called
        TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);                  //Enable interrupts
        TCCR1B |= (1 << CS12) | (1 << CS10);                    //Configure prescaler (prescaler = 1024)
    }
};

/*
 * Enables interrupts globally. Should preferrably only start the timer, but for this application it works
 */

void timer_ms::start() {
    sei();
}

/*
 * Disables interrupts globally. Should preferrably only stop the timer, but for this application it works
 */

void timer_ms::stop() {
    cli();
}

/*
 * Change the OCR1B register to change the time when interrupt B triggers. This is used to generate a PWM signal.
 * the duty variable should be between 1 and 99. Practically speaking, the duty cycle only works between 7 and 95.
 */

void timer_ms::setDutyCycle(uint16_t duty) {
    mDutyCycle = duty;
    //Update the OCR1B register. This is set up to prevent memory overflow
    OCR1B = (160 * static_cast<float>(mTimerInterval * mDutyCycle) / 1024) - 1;
    //OCR1B = ((((160*100) / 1024)*mTimerInterval)/100)*mDutyCycle-1;
}

uint16_t timer_ms::getInterval() {
    return mTimerInterval;
}

uint16_t timer_ms::getDutyCycle() {
    return mDutyCycle;
}