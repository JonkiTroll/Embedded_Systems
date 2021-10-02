//
// Created by jon on 9/19/21.
//

#ifndef ARDUINO_PID_PI_CONTROLLER_H
#define ARDUINO_PID_PI_CONTROLLER_H

#include "controller.h"

class pi_controller : controller{
public:
    pi_controller(double p, double i,  double limit_min, double limit_max, double sampleT) :
            controller(0, limit_min, limit_max, sampleT), K_p(p), K_i(i) {
        integrator = 0.0;

    }

    double update(double setPoint, double measurement) override
    {
        /* Error signal */
        double error = setPoint-measurement;
        /* Proportional */
        double proportional = K_p * error;

        /* Integral */
        integrator = integrator + K_i*T*(error);

        double limMinInt, limMaxInt;

        //Anti-wind-up via dynamic integrator clamping
        if(limMax > proportional) {
            limMaxInt = limMax - proportional;
        } else {
            limMaxInt = 0.0;
        }

        if(limMax < proportional) {
            limMinInt = limMin - proportional;
        } else {
            limMinInt = 0.0;
        }

        /* Clamp integrator */

        if (integrator > limMaxInt) {
            integrator = limMaxInt;
        } else if (integrator < limMinInt) {
            integrator = limMinInt;
        }


        double result = proportional + integrator;

        if (result > limMax) {
            result = limMax;
        } else if (result < limMin) {
            result = limMin;
        }

        return result;
    }

private:
    const double K_p, K_i;
    double integrator;
};


#endif //ARDUINO_PID_PI_CONTROLLER_H
