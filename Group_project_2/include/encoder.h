//
// Created by group 2 on 15/09/21.
//

#ifndef GROUP_PROJECT_1_ENCODER_H
#define GROUP_PROJECT_1_ENCODER_H

#include <stdio.h>

class encoder
{
public:
    encoder() : DRV_PIN1(0), DRV_PIN2(0) {}

    void init(int pin1, int pin2, int interrupt_pin);
    void turn_on();
    void turn_off();
    void calc_speed_micros(uint32_t time_micros);
    int getPPS() const;

    uint32_t getTau() const;

private:
    bool measurement = false;
    unsigned long curr_time = 0;
    uint32_t old_time_micros = 0;
    const uint8_t N = 10;
    int16_t PPS[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t head = 0;
    int32_t cum_sum = 0;
    uint32_t tau = 0;
    uint8_t DRV_PIN1;
    uint8_t DRV_PIN2;
};

#endif //GROUP_PROJECT_1_ENCODER_H
