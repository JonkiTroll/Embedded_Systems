//
// Created by jon on 9/30/21.
//

#ifndef GROUP_PROJECT_3_STATE_H
#define GROUP_PROJECT_3_STATE_H

#include "Arduino.h"

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
    virtual void fault() = 0;
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
        }  else if(command == 's') {
            this->state_->fault();
        } else {
            Serial.print("Invalid command\n\r");
        }
    }
};


#endif //GROUP_PROJECT_3_STATE_H
