//
// Created by jon on 9/19/21.
//

#ifndef ARDUINO_PID_PI_CONTROLLER_H
#define ARDUINO_PID_PI_CONTROLLER_H

#include "controller.h"

class pid_controller : controller{
public:
    pid_controller(double p, double i, double d, double t, double limit_min, double limit_max, double sampleT) :
            controller(t, limit_min, limit_max, sampleT), K_p(p), K_i(i), K_d(d) {
        integrator = 0.0;
        differentiator = 0.0;

        prevError = 0.0;
        prevMeasurement = 0.0;
    }

    double update(double setPoint, double measurement) override
    {
        /* Error signal */
        double error = setPoint-measurement;
        /* Proportional */
        double proportional = K_p * error;

        /* Integral */
        integrator = integrator + 0.5*K_i*T*(error+prevError);

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
        /* Derivative term */
        differentiator = (2 * K_d * (measurement - prevMeasurement)
                + (2 * tau - T) * differentiator)
                / (2 * tau+T);


        double result = proportional + integrator + differentiator;

        if (result > limMax) {
            result = limMax;
        } else if (result < limMin) {
            result = limMin;
        }

        prevError = error;
        prevMeasurement = measurement;

        return result;
    }

    void reset() override {
        integrator = 0.0;
        prevError = 0.0;
        differentiator = 0.0;
        prevMeasurement = 0.0;
    }

private:
    const double K_p, K_i, K_d;
    double integrator;
    double prevError;
    double differentiator;
    double prevMeasurement;
};


#endif //ARDUINO_PID_PI_CONTROLLER_H
