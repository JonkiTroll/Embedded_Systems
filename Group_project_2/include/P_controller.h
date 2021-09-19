//
// Created by jon on 9/19/21.
//

#pragma once

class P_controller {
public:
    P_controller(double K) : K_p(K){}

    double update(double ref, double actual){
        return K_p*(actual-ref);
    }

private:
    const double K_p;
};

