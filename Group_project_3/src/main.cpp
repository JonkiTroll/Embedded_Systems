//
// Created by jon on 9/16/21.
//
#include "State.h"
#include "states/Initialization.h"
#include "states/Operational.h"
#include "states/Stopped.h"
#include "avr/interrupt.h"
#include "main.h"

//timer_8bit timer0(10);
timer_ms timer1(500);
Digital_out led(5);
Digital_in fault(1);
Context *context;
// missing the controller
void setup(){

    Serial.begin(115200);

    context = new Context(new Initialization);
}

char command;

void loop(){

    while (command == '0') {
        if (Serial.available())
            command = Serial.read();
        /*
        if(fault.is_hi()) {
            command = 's';

         }
         */


    }
    if (command != '0')
        context->Request1(command);
    command = '0';

}

ISR(TIMER1_COMPA_vect) {
    led.toggle();
}