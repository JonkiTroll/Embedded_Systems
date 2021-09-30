//
// Created by jon on 9/30/21.
//

#ifndef GROUP_PROJECT_3_STOPPED_H
#define GROUP_PROJECT_3_STOPPED_H

#include "State.h"

class Stopped : public State {
public:
    Stopped() {}
    void on_entry() override;
    void on_exit() override;
    void blinkLed() override;
    void reset() override {}
    void fault() override;
    void clearFault() override;

};

#endif //GROUP_PROJECT_3_STOPPED_H
