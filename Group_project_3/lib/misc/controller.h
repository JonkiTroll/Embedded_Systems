//
// Created by jon on 9/19/21.
//

#ifndef ARDUINO_PLANTUML_CONTROLLER_H
#define ARDUINO_PLANTUML_CONTROLLER_H


class controller {
public:
    controller(double t, double limit_min, double limit_max, double sampleT) :
    tau(t), limMin(limit_min), limMax(limit_max), T(sampleT) {}
    virtual double update(double setPoint, double measurement) = 0;

protected:
    const double tau;
    const double limMin;
    const double limMax;
    const double T;


};


#endif //ARDUINO_PLANTUML_CONTROLLER_H
