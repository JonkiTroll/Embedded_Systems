//
// Created by jon on 9/19/21.
//

#pragma once
#include "Arduino.h"
#include <math.h>

class P_controller {
public:
    P_controller(double K, double T) : K_p(K), threshold(T){}

    double update(double ref, double actual){

        double speed = K_p*(ref-actual) + ref;

        double error = fabs((ref-actual)/ref);

        if (error > threshold) {
            old_speed = speed;
            return speed;
        } else {
            return old_speed;
        }
    }

private:
    double old_speed;
    const double K_p;
    const double threshold;
};

