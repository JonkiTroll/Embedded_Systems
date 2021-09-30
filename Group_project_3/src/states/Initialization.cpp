//
// Created by jon on 9/30/21.
//
#include "states/Initialization.h"
#include "states/Operational.h"
#include "main.h"

void Initialization::on_entry()  {
    Serial.println("Entering Initialization");

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

