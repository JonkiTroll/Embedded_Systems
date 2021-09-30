//
// Created by jon on 9/30/21.
//

#ifndef GROUP_PROJECT_3_MAIN_H
#define GROUP_PROJECT_3_MAIN_H

#include "digital_out.h"
#include "digital_in.h"
#include "timer_8bit.h"
#include "Arduino.h"
#include "encoder.h"
#include "P_controller.h"


extern timer_8bit timer0;
extern encoder motor;
extern P_controller speed_controller;

extern Digital_out led;

#endif //GROUP_PROJECT_3_MAIN_H
