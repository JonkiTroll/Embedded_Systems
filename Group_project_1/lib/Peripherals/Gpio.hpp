//
// Created by jon on 8/20/21.
//

#ifndef ARDUINO_INT_TEST_GPIO_H
#define ARDUINO_INT_TEST_GPIO_H

#include <stdint.h>
#include <avr/io.h>

enum IO{
    GPIO_Input,
    GPIO_Output,
};

class Gpio {
public:


    Gpio(uint8_t pin, volatile uint8_t *port, uint8_t IO);

    ~Gpio() = default;;

    void set();
    void clear();
    void toggle();
    uint8_t getPin() const;
    bool read() const;

private:
    uint8_t mPinBit;
    const uint8_t pin;
    volatile uint8_t *mPort; //The port is kept as a volatile pointer.
                            //volatile -> the value of the port can change without the program doing it.


};


#endif //ARDUINO_INT_TEST_GPIO_H
