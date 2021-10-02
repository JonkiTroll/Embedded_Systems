//
// Created by jon on 9/30/21.
//

#ifndef GROUP_PROJECT_3_OPERATIONAL_H
#define GROUP_PROJECT_3_OPERATIONAL_H

#include "State.h"

class Operational : public State {
public:
    Operational() {

    }

    void on_entry() override;

    void on_exit() override;

    void on_loop() override;

    void blinkLed() override;
    void reset() override;
    void fault() override;
    void preOp() override;

};

#endif //GROUP_PROJECT_3_OPERATIONAL_H
