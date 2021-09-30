//
// Created by jon on 9/30/21.
//
#include "states/Operational.h"
#include "states/Initialization.h"
#include "states/Stopped.h"
#include "main.h"

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
    int16_t reference_speed = 1000;//(duty*1266)/100;
    int32_t updated_speed = speed_controller.update(reference_speed, motor.get_average());
    motor.update_speed(updated_speed);

    Serial.print("Updated_speed: ");
    Serial.println(updated_speed);
    Serial.println();

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