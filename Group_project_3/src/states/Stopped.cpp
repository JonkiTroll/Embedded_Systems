//
// Created by jon on 9/30/21.
//

#include "states/Stopped.h"
#include "states/Operational.h"
#include "main.h"

void Stopped::on_entry() {
    Serial.println("Entering Stopped");
    motor.turn_off();
    this->blinkLed();
}

void Stopped::on_exit() {

    timer0.disable();
    motor.turn_on();
    Serial.println("Exiting Stopped");
}

void Stopped::blinkLed() {

    timer0.enable();
}

void Stopped::fault() {
    Serial.println("Clearing fault");
    this->context_->TransitionTo(new Operational);
}
