//
// Created by jon on 10/2/21.
//

#ifndef GROUP_PROJECT_3_PREOPERATIONAL_H
#define GROUP_PROJECT_3_PREOPERATIONAL_H

#include "State.h"

class preOperational : public State {
public:
    preOperational() {
        counter = 0;
    }

    void on_entry() override;

    void on_exit() override;

    void on_loop() override;

    void blinkLed() override;
    void reset() override;
    void fault() override;
private:
    uint16_t counter;
};

#endif //GROUP_PROJECT_3_PREOPERATIONAL_H
