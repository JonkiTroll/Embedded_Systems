//
// Created by group 2 on 15/09/21.
//

#ifndef GROUP_PROJECT_1_ENCODER_H
#define GROUP_PROJECT_1_ENCODER_H

#include <stdio.h>

class encoder {
public:
    encoder();

    void init(int pin1, int pin2);
    void update_count();
    double calculate_speed();
    void calc_speed_micros(uint16_t time_micros);
    int getPPS();
    int calculate_average();
private:
    const int32_t PPR = 700; //Pulses per revolution. Replace with actual pulses per revolution
    int32_t count;
    uint32_t old_time_micros;
    uint8_t N = 5;
    int16_t PPS[5] = {0, 0, 0, 0, 0};
    uint8_t head;
    int32_t cum_sum = 0;
    
};


#endif //GROUP_PROJECT_1_ENCODER_H
