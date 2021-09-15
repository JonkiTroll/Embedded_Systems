//
// Created by jon on 9/15/21.
//

#ifndef GROUP_PROJECT_1_ENCODER_H
#define GROUP_PROJECT_1_ENCODER_H

#include <stdio.h>

class encoder {
public:
    encoder();

    void update_count();
    double calculate_speed();
private:
    const int32_t PPR = 700; //Pulses per revolution. Replace with actual pulses per revolution
    int32_t count;
};


#endif //GROUP_PROJECT_1_ENCODER_H
