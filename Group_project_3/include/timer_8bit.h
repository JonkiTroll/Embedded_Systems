//
// Created by jon on 9/19/21.
//

#ifndef GROUP_PROJECT_2_TIMER_8BIT_H
#define GROUP_PROJECT_2_TIMER_8BIT_H
#include "avr/interrupt.h"

class timer_8bit {
public:
    timer_8bit(uint16_t timer_interval)
    {
        interval = timer_interval;
        counter = 0;
    }
    void init()
    {
        TCCR0A = 0; //Clear Timer0 register A
        TCCR0B = 0; //Clear Timer0 register B
        TCNT0 = 0;  //Clear counter

        OCR0A |= ((16000) / 1024) * interval - 1;

        TCCR0A |= (1 << WGM01); //CTC mode. Clear on compare match
        TCCR0A |= (1 << COM0A0); //Toggle OC0A on compare match

        TCCR0B |= (1 << CS00) | (0 << CS01) | (1 << CS02);

        //this->disable(); //Only start timer when user asks for it
 
    }

    void enable() {
        TIMSK0 |= (1 << OCIE0A);
    }

    void disable() {
        TIMSK0 &= ~(1 << OCIE0A);
    }

    void setInterval(uint16_t i) {
        i = interval;
        OCR0A |= ((16000) / 1024) * interval - 1;
    }

    void setCounter(uint16_t value) {
        counter = value;
    }

    uint16_t getCounter() const {
        return counter;
    }

private:
    uint16_t interval;
    uint16_t counter;

};


#endif //GROUP_PROJECT_2_TIMER_8BIT_H
