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
    virtual void on_entry() { }
    virtual void on_exit() { }
    virtual void on_loop() {  }
    virtual void blinkLed() {  }
    virtual void reset() {  }
    virtual void fault() { }
    virtual void set() {  }
    virtual void preOp() {  }
    virtual void clearFault() { }
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
    uint8_t Request1(uint16_t command) {
        switch (command) 
        {
            case 81:
                this->state_->reset();
                return 0;
            case 2:
                this->state_->fault();
                return 0;
            case 82:
                this->state_->clearFault();
                return 0;
            case 80:
                this->state_->preOp();
                return 0;
            case 1:
                this->state_->set();
                return 0;
            case 0x00FF:
                this->state_->on_loop();
                return 0;
            default:
                return 3;
                //Serial.print("Invalid command");
                
        }
    }
};


#endif //GROUP_PROJECT_3_STATE_H
