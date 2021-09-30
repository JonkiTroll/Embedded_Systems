//
// Created by jon on 9/16/21.
//
#include "State.h"
#include "Initialization.h"
#include "Operational.h"
#include "Stopped.h"
#include "main.h"

Digital_out led(5);
Context *context;

void setup(){

    Serial.begin(115200);
    led.init();

    context = new Context(new Initialization);
}

char command;

void loop(){

    while (command == '0') {
            if (Serial.available())
                command = Serial.read();

    }
    if (command != '0')
        context->Request1(command);
    command = '0';

   }