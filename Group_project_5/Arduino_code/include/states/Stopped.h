//
// Created by jon on 9/30/21.
//

#ifndef GROUP_PROJECT_3_STOPPED_H
#define GROUP_PROJECT_3_STOPPED_H

#include "State.h"

class Stopped : public State {
public:
    explicit Stopped(char old_context) : old_context_(old_context) {}
    void on_entry() override;
    void on_exit() override;
    void blinkLed() override;
    void reset() override;
    void clearFault() override;
private:
    const char old_context_;
};

#endif //GROUP_PROJECT_3_STOPPED_H
