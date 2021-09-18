//
// Created by group 2 on 15/09/21.
//

#ifndef GROUP_PROJECT_1_ENCODER_H
#define GROUP_PROJECT_1_ENCODER_H

#include <stdio.h>

class encoder
{
public:
    encoder();

    void init(int pin1, int pin2, int interrupt_pin);
    void turn_on();
    void turn_off();
    void change_dir();
    void update_count();
    double calculate_speed();
    void calc_speed_micros(uint16_t time_micros);
    int getPPS();
    int calculate_average();
    uint32_t tau = 0;

private:
    const int32_t PPR = 700; //Pulses per revolution. Replace with actual pulses per revolution
    bool measurement = false;
    int32_t count;
    uint32_t old_time_micros;
    uint8_t N = 10;
    int16_t PPS[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t head;
    int32_t cum_sum = 0;
    uint8_t DRV_PIN1;
    uint8_t DRV_PIN2;
};

#endif //GROUP_PROJECT_1_ENCODER_H
