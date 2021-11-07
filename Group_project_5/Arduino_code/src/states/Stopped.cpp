//
// Created by jon on 9/30/21.
//

#include "states/Stopped.h"
#include "states/Operational.h"
#include "states/preOperational.h"
#include "states/Initialization.h"
#include "main.h"

void Stopped::on_entry() {
    //Serial.println("Entering Stopped");
    this->blinkLed();
}

void Stopped::on_exit() {

    timer0.disable();
    //Serial.println("Exiting Stopped");
}

void Stopped::blinkLed() {
    timer0.setCounter(500);
    timer0.enable();
}

void Stopped::clearFault() {
    //Serial.println("Clearing fault");
    if (old_context_ == 'o') {
        this->context_->TransitionTo(new Operational);
    } else if (old_context_ == 'p') {
        this->context_->TransitionTo(new preOperational);
    }
}

void Stopped::reset() {
    this->context_->TransitionTo(new Initialization);
}
