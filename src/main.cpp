//
// Created by jon on 8/18/21.
//
#include <util/delay.h>
#include "digital_in.h"
#include "digital_out.h"


int main() {

    Digital_in encoderA(0);
    Digital_in encoderB(1);
    Digital_out led(5);

    int8_t increment = 0;
    bool flag = false;

    encoderA.init();
    encoderB.init();
    led.init();

    while(true){

        if(encoderA.is_hi() && !flag){
            increment++;
            flag = true;
        } else if (encoderB.is_hi() && !flag) {
            increment--;
            flag = true;
        } else if (encoderA.is_lo() && encoderB.is_lo()) {
            flag = false;
        }

        if(increment >= 126){
            increment = 0;
            led.toggle();

        }
    }


    return 0;

}



//static_assert((pin >= 0 && pin <=13), "Invalid pin! choose between 0 and 13!"); //Compile time assert!! Doesn't work in the class though.