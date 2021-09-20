//
// Created by jon on 9/19/21.
//

#pragma once
#include "Arduino.h"
#include <math.h>

#define DEBUG

class P_controller {
public:
    P_controller(double K, double T, int32_t max_limit, int32_t min_limit) :
    K_p(K), threshold(T), limMax(max_limit), limMin(min_limit) {

    }

    int32_t update(int16_t ref, int16_t actual){

        auto speed = static_cast<int32_t>(K_p*(ref-actual));
#ifdef DEBUG
        Serial.print("actual speed: ");
        Serial.println(actual);
        Serial.print("reference speed: ");
        Serial.println(ref);
        Serial.print("calculated speed: ");
        Serial.println(speed);
#endif
        double error = fabs(static_cast<double>((ref-actual))/ref);
#ifdef DEBUG
        Serial.print("Error: ");
        Serial.println(error);
#endif
        if ( speed > limMax) {
            return limMax;
        } else if (speed < limMin) {
            return limMin;
        }

        if (error > threshold) {
            old_speed = speed;
            return speed;
        } else {
            return old_speed;
        }
    }

private:
    int32_t old_speed;
    const double K_p;
    const double threshold;
    const int32_t limMax, limMin;
};

