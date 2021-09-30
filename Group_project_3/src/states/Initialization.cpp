//
// Created by jon on 9/30/21.
//
#include "states/Initialization.h"
#include "states/Operational.h"
#include "main.h"

void Initialization::on_entry()  {
    Serial.println("Entering Initialization");
    // Maybe set here the useage of initalization so that when this restarts, everything is reset.
    // Torfi says no, but not sure.
    cli();
    led.init();
    timer1.init();
    delay(100);
    led.set_lo();
    delay(100);
    sei();

    this->context_->TransitionTo(new Operational);
}

void Initialization::on_exit() {

    Serial.println("Boot finished");
}

