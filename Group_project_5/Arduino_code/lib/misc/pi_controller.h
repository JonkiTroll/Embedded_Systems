//
// Created by jon on 9/19/21.
//

#ifndef ARDUINO_PID_PI_CONTROLLER_H
#define ARDUINO_PID_PI_CONTROLLER_H

#include "controller.h"
#include "math.h"

class pi_controller : public controller
{
public:
    pi_controller(double p, double i,  double limit_min, double limit_max, double sampleT) :
            controller(0, limit_min, limit_max, sampleT)
    {
        K_p = p;
        K_i = i;
        integrator = 0.0;

    }

    double update(double setPoint, double measurement) override
    {
        bool Forward = true;
        if (setPoint < 0) {
            setPoint = -setPoint;
            Forward = false;
        }

        if (measurement < 0) {
            measurement = -measurement;
        }
        /* Error signal */
        double error = setPoint-(measurement);
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

        if(Forward){
            return result;
        } else {
            return -result;
        }

    }

    void reset() override {
        integrator = 0.0;
    }

    void setProportionalGain( double newValue) {
        K_p = newValue;
    }
    double getProportionalGain() const {
        return K_p;
    }

    void setIntegralGain( double newValue) {
        K_i = newValue;
    }
    double getIntegralGain() const{
        return K_i;
    }

private:
    double K_p, K_i;
    double integrator;
};


#endif //ARDUINO_PID_PI_CONTROLLER_H
