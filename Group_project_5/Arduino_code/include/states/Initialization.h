//
// Created by jon on 9/30/21.
//

#ifndef GROUP_PROJECT_3_INITIALIZATION_H
#define GROUP_PROJECT_3_INITIALIZATION_H

#include "State.h"

class Initialization : public State {
public:
    Initialization() {};
    void on_entry() override;
    void on_exit() override;
    void blinkLed() override {}
    void reset() override {}
    void fault() override {}

};
#endif //GROUP_PROJECT_3_INITIALIZATION_H
