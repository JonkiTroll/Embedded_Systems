//
// Created by jon on 9/19/21.
//

#pragma once
#include "Arduino.h"
#include <math.h>

#define DEBUG

class P_controller {
public:
    P_controller(double K, double T) :
    K_p(K), threshold(T){

    }
    /*
     * Update function for the P controller. Takes in the feedback from the system as the actual term and reference
     * and calculates
     */

    int32_t update(int16_t ref, int16_t actual){

        //calculate the output of the system using control law
        auto output = static_cast<int32_t>(K_p * (ref - actual));

#ifdef DEBUG
        Serial.print("actual output: ");
        Serial.println(actual);
        Serial.print("reference output: ");
        Serial.println(ref);
        Serial.print("calculated output: ");
        Serial.println(output);
#endif
        //Calculate error as an absolute term
        double error = fabs(static_cast<double>((ref-actual))/ref);
#ifdef DEBUG
        Serial.print("Error: ");
        Serial.println(error);
#endif
        //Threshold to avoid unnecessary changes in output
        if (error > threshold) {
            old_speed = output;
            return output;
        } else {
            return old_speed;
        }
    }

private:
    int32_t old_speed;
    const double K_p;
    const double threshold;
};

