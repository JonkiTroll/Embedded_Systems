//
// Created by jon on 10/2/21.
//

#include "states/preOperational.h"
#include "states/Operational.h"
#include "states/Initialization.h"
#include "states/Stopped.h"
#include "main.h"

#define DEBUG


void preOperational::on_entry(){
    this->blinkLed();
    
}

void preOperational::on_exit()  {
    timer0.disable();
    //Serial.println("Leaving preOperational");
}

void preOperational::on_loop() {
   /*
    counter++;
    if (counter > 500) {
        this->context_->TransitionTo(new Operational);
    }
    delay(10);
    */
}

void preOperational::blinkLed() {
    timer0.setCounter(1000);
    timer0.enable();
}

void preOperational::reset()  {
    //Serial.println("Resetting");
    this->context_->TransitionTo(new Initialization);
}

void preOperational::fault() {
    this->context_->TransitionTo(new Stopped('p'));
}

void preOperational::set() {
    this->context_->TransitionTo(new Operational);
}

void preOperational::preOp() {
    //enterShell();
    
}

void preOperational::enterShell() {
    bool leave = false;
    Serial.setTimeout(120000);
    while(!leave) {
        Serial.write(27);       // ESC command
        Serial.print("[2J");    // clear screen command
        Serial.write(27);
        Serial.print("[H");     // cursor to home command
        Serial.println("============================================================");
        Serial.println("Select which parameter you wish to edit");
        Serial.print("proportional gain: p<new value> \t current value: ");
        Serial.println(speed_controller.getProportionalGain());
#ifndef USE_P_CONTROLLER
        Serial.print("integral gain: i<new value> \t\t current value: ");
        Serial.println(speed_controller.getIntegralGain());
#endif
        Serial.print("reference speed: r<new value> \t\t current value: ");
        Serial.println(reference);
        Serial.println("q: quit");
        Serial.println("============================================================");

        double newVal;
        String command = Serial.readStringUntil('\r');

        switch (command.c_str()[0]) {
            case 'p':
                command.remove(0, 1);
                newVal = command.toDouble();
                speed_controller.setProportionalGain(newVal);
                break;
#ifndef USE_P_CONTROLLER
            case 'i':
                command.remove(0, 1);
                newVal = command.toDouble();
                speed_controller.setIntegralGain(newVal);
                break;
#endif
            case 'r':
                command.remove(0, 1);
                newVal = command.toDouble();
                reference = newVal;
                break;
            case 'q':
                leave = true;
                Serial.setTimeout(1000);
                Serial.write(27);       // ESC command
                Serial.print("[2J");    // clear screen command
                Serial.write(27);
                Serial.print("[H");     // cursor to home command
                Serial.println("leaving Shell");
                Serial.println("e: Start motor");
                Serial.println("r: reset system");
                Serial.println("s: Stop system");
                Serial.println("p: return to shell");
                break;
            default:
                Serial.println("Invalid command");
        }
    }


}