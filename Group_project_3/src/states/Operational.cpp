//
// Created by jon on 9/30/21.
//
#include "states/Operational.h"
#include "states/Initialization.h"
#include "states/Stopped.h"
#include "main.h"

void Operational::on_entry(){
    Serial.println("Entering Operational");
    this->blinkLed();
}

void Operational::on_exit()  {
    Serial.println("Leaving Operational");
}

void Operational::blinkLed() {
        led.set_hi();
}

void Operational::reset()  {
    Serial.println("Resetting");
    this->context_->TransitionTo(new Initialization);
}

void Operational::fault() {
    this->context_->TransitionTo(new Stopped);
}