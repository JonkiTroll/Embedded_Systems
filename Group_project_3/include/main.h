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

//#define USE_P_CONTROLLER

#ifdef USE_P_CONTROLLER
#include "p_controller.h"
#else
#include "pi_controller.h"
#endif

extern timer_8bit timer0;
extern encoder motor;

#ifdef USE_P_CONTROLLER
extern p_controller speed_controller;
#else
extern pi_controller speed_controller;
#endif

extern Digital_out led;

#endif //GROUP_PROJECT_3_MAIN_H
