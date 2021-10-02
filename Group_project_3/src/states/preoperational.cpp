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
    Serial.println("Entering preOperational");
    this->blinkLed();
}

void preOperational::on_exit()  {
    timer0.disable();
    Serial.println("Leaving preOperational");
}

void preOperational::on_loop() {
    counter++;
    if (counter > 500) {
        this->context_->TransitionTo(new Operational);
    }
    delay(10);
}

void preOperational::blinkLed() {
    timer0.setCounter(1000);
    timer0.enable();
}

void preOperational::reset()  {
    Serial.println("Resetting");
    this->context_->TransitionTo(new Initialization);
}

void preOperational::fault() {
    this->context_->TransitionTo(new Stopped);
}