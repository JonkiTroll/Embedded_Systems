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
    void Request1(uint8_t command) {
        switch (command) 
        {
            case 0x81:
                this->state_->reset();
                break;
            case 0x02:
                this->state_->fault();
                break;
            case 0x82:
                this->state_->clearFault();
                break;
            case 0x80:
                this->state_->preOp();
                break;
            case 0x01:
                this->state_->set();
                break;
            case 'l':
                this->state_->on_loop();
                break;
            default:
                //Serial.print("Invalid command");
                break;
        }
    }
};


#endif //GROUP_PROJECT_3_STATE_H
