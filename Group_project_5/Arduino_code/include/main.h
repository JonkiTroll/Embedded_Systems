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

/*
 * Uncomment this to use P controller instead of PI controller
 */
<<<<<<< HEAD
//#define USE_P_CONTROLLER
=======
// #define USE_P_CONTROLLER
>>>>>>> 9e9f2517a7731650a2245806cfd852385eb1ac47

#ifdef USE_P_CONTROLLER
#include "p_controller.h"
#else
#include "pi_controller.h"
#endif

#ifdef USE_P_CONTROLLER
extern p_controller speed_controller;
#else
extern pi_controller speed_controller;
#endif

extern timer_8bit timer0;
extern encoder motor;
extern Digital_out led;
extern double reference;
extern const uint16_t period_ms;

#endif //GROUP_PROJECT_3_MAIN_H
