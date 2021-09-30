//
// Created by jon on 9/30/21.
//

#include "states/Stopped.h"
#include "states/Operational.h"
#include "main.h"

void Stopped::on_entry() {
    Serial.println("Entering Stopped");

    this->blinkLed();
}

void Stopped::on_exit() {

    timer1.disable();
    Serial.println("Exiting Stopped");
}

void Stopped::blinkLed() {
    timer1.setInterval(500);
    timer1.enable();
}

void Stopped::fault() {
    Serial.println("Clearing fault");
    this->context_->TransitionTo(new Operational);
}
