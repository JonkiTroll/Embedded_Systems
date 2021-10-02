//
// Created by jon on 9/30/21.
//
#include "states/Operational.h"
#include "states/Initialization.h"
#include "states/Stopped.h"
#include "main.h"

#define DEBUG

void Operational::on_entry(){
    Serial.println("Entering Operational");
    motor.turn_on();
    this->blinkLed();
}

void Operational::on_exit()  {
    Serial.println("Leaving Operational");
}

void Operational::on_loop() {

    _delay_ms(100);
    double reference_speed = 1000.0;//(duty*1266)/100;
    auto measured_speed = static_cast<double>(motor.get_average());

    auto updated_speed = static_cast<int32_t>(speed_controller.update(reference_speed,
                                                   measured_speed));
    motor.update_speed(updated_speed);
#ifdef DEBUG
    Serial.print("Actual speed: ");
    Serial.println(measured_speed);
    Serial.print("Updated_speed: ");
    Serial.println(updated_speed);
    Serial.println();
#endif

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