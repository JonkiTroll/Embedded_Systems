//
// Created by jon on 9/19/21.
//

#ifndef ARDUINO_PLANTUML_P_CONTROLLER_H
#define ARDUINO_PLANTUML_P_CONTROLLER_H

#include "controller.h"

class p_controller : controller {
public:
    p_controller(double p,  double limit_min, double limit_max) :
                                                                controller(0, limit_min, limit_max, 0), K_p(p) {

    }

    double update(double setPoint, double measurement) override
    {
        double error = setPoint-measurement;
        double proportional = K_p * error;

        if (proportional > limMax) {
            return limMax;
        } else if (proportional < limMin) {
            return limMin;
        }

        return proportional;
    }

private:
    const double K_p;
};


#endif //ARDUINO_PLANTUML_P_CONTROLLER_H
