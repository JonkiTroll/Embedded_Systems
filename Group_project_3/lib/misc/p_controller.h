//
// Created by jon on 9/19/21.
//

#ifndef ARDUINO_PLANTUML_P_CONTROLLER_H
#define ARDUINO_PLANTUML_P_CONTROLLER_H

#include "controller.h"

class p_controller : public controller {
public:
    p_controller(double p,  double limit_min, double limit_max) :
                                                                controller(0, limit_min, limit_max, 0), K_p(p) {

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

        double error = setPoint-measurement;
        double proportional = K_p * error;

        if (proportional > limMax) {
            proportional = limMax;
        } else if (proportional < limMin) {
            proportional = limMin;
        }

        if(Forward){
            return proportional;
        } else {
            return -proportional;
        }
    }

    void reset() override {

    }

    void setProportionalGain( double newValue){
        K_p = newValue;
    }
    double getProportionalGain() const{
        return K_p;
    }

private:
    double K_p;

};


#endif //ARDUINO_PLANTUML_P_CONTROLLER_H
