//
// Created by jon on 9/30/21.
//
#include "states/Initialization.h"
#include "states/preOperational.h"
#include "main.h"


constexpr uint8_t interrupt_pin = 0;

void Initialization::on_entry()  {
    //Serial.println("Entering Initialization");
    // Maybe set here the useage of initalization so that when this restarts, everything is reset.
    // Torfi says no, but not sure.
    cli();
    speed_controller.reset();
    led.init();
    delay(100);
    led.set_lo();
    delay(100);
    motor.init(interrupt_pin);

    sei();

    this->context_->TransitionTo(new preOperational);
}

void Initialization::on_exit() {

    //Serial.println("Boot finished");
}

