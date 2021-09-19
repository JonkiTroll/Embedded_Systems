//
// Created by group 2 on 15/09/21.
//

#ifndef GROUP_PROJECT_1_ENCODER_H
#define GROUP_PROJECT_1_ENCODER_H

#include <stdio.h>
#include "timer_ms.h"
#include "avr/interrupt.h"

#define ARRAY_LENGTH    10

extern "C"{
    ISR(TIMER1_COMPA_vect);
    ISR(TIMER1_COMPB_vect);
};

class encoder
{
public:
    encoder() : DRV_PIN1(0), DRV_PIN2(0), timer1(0, 100) {}
    encoder(uint16_t intervalMs, uint16_t dutyCycle)
    : DRV_PIN1(0), DRV_PIN2(0), timer1(intervalMs, dutyCycle) {}


    void init(int pin1, int pin2, int interrupt_pin);
    void turn_on();
    void turn_off();
    void calc_speed_micros(uint32_t time_micros);
    int getPPS() const;
    void update_speed(double new_speed);

    uint32_t getTau() const;


private:
    bool measurement = false;
    unsigned long curr_time = 0;
    uint32_t old_time_micros = 0;
    const uint8_t N = ARRAY_LENGTH;
    const uint16_t top_speed = 1266;
    int16_t PPS[ARRAY_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t head = 0;
    int32_t cum_sum = 0;
    uint32_t tau = 0;
    uint8_t DRV_PIN1;
    uint8_t DRV_PIN2;
    timer_ms timer1;
};

#endif //GROUP_PROJECT_1_ENCODER_H
