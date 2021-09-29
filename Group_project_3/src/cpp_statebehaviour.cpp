//
// Created by jon on 9/16/21.
//
#include <Arduino.h>
#include "digital_out.h"
/**
 * The base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Context object, associated
 * with the State. This backreference can be used by States to transition the
 * Context to another State.
 */

bool TimeOut = false;
Digital_out led(5);


class Context;

class State {
    /**
     * @var Context
     */
protected:
    Context *context_;

public:
    virtual ~State() {
    }

    void set_context(Context *context) {
        this->context_ = context;
    }
    virtual void on_entry() = 0;
    virtual void on_exit() = 0;
    virtual void blinkLed() = 0;
    virtual void reset() = 0;
};

/**
 * The Context defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Context.
 */
class Context {
    /**
     * @var State A reference to the current state of the Context.
     */
private:
    State *state_;

public:
    Context(State *state) : state_(nullptr) {
        this->TransitionTo(state);
    }

    ~Context() {
        delete state_;
    }

    /**
     * The Context allows changing the State object at runtime.
     */
    void TransitionTo(State *state) {

        if (this->state_ != nullptr) {
            this->state_->on_exit();
            delete this->state_;
        }
        this->state_ = state;
        this->state_->set_context(this);
        this->state_->on_entry();
    }

    /**
     * The Context delegates part of its behavior to the current State object.
     */
    void Request1(char command) {
        if(command == 'r'){
            this->state_->reset();
        }  else {
            Serial.print("Invalid command\n\r");
        }
    }
};

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class Initialization : public State {
public:
    Initialization() {};
    void on_entry() override;
    void on_exit() override;
    void blinkLed() override {};
    void reset() override {};

};


class Operational : public State {
public:
    Operational() {

    }

    void on_entry() override {
        Serial.println("Entering Operational");

        this->blinkLed();
    }

    void on_exit() override {
        Serial.println("Leaving Operational");
    };

    void blinkLed() override {
        led.set_hi();
    };
    void reset() override {
        Serial.println("Resetting");
        this->context_->TransitionTo(new Initialization);
    };
};

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


/**
 * The client code.
 */

Context *context;

void setup(){

    Serial.begin(115200);
    led.init();

    context = new Context(new Initialization);
}

char command;

void loop(){

    while (command == '0') {
            if (Serial.available())
                command = Serial.read();

    }
    if (command != '0')
        context->Request1(command);
    command = '0';

   }