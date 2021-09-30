//
// Created by jon on 9/30/21.
//
#include "Initialization.h"
#include "Operational.h"
#include "main.h"

void Initialization::on_entry()  {
    Serial.println("Entering Initialization");
    delay(100);
    led.set_lo();
    delay(100);
    this->context_->TransitionTo(new Operational);
}

void Initialization::on_exit() {

    Serial.println("Boot finished");
}

