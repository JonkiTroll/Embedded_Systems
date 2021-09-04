#include "digital_in.h"
#include "digital_out.h"


int main() {
    
    //local variables. The Encoders are initialized on PORTB
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
            led.set_hi();
        } else if (encoderB.is_hi() && !flag) {
            increment--;
            flag = true;
            led.set_hi();
        } else if (encoderA.is_lo() && encoderB.is_lo()) {
            flag = false;
            led.set_lo();
        }
    }
    return 0;

}