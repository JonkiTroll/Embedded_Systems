//
// Created by jon on 8/20/21.
//

#include "Gpio.hpp"


Gpio::Gpio(const uint8_t pin, const uint8_t IO) : pin(pin){

    uint8_t portPin;
    volatile uint8_t *initPort;

    if (pin <= 7) {
        portPin = pin;
        mPort = &PORTD; //m -> member variable
        initPort = &DDRD;

    } else if (pin <= 13) {
        portPin = pin - 8;
        mPort = &PORTB;
        initPort = &DDRB;
    } else {
        return;
    }

    mPinBit = (1 << portPin); //left bitwies shift to get the bit for the pin

    //Configure the object as either input or output.
    switch (IO) {
        case GPIO_Output:
            initPort -= 1U; //when configuring to output, the addresses of both ports need to re reduced by 1. Else it won't work
            mPort -= 1U;
            *initPort |= mPinBit; //set the
        case GPIO_Input:
            *initPort &= ~mPinBit;
            this->set(); //enable internal pull-up
        default:
            break;
    }
}

/*
 * Sets the gpio output high.
 * turns the internal pullup on for input configured pins
 */
void Gpio::set() {
    *mPort |= mPinBit;
}
/*
 * sets the gpio output low
 * turns the internal pullup off for input configured pins
 */
void Gpio::clear() {
    *mPort &= ~mPinBit;
}
/*
 * Inverses the pin state
 * toggles internal pullup for input configured pins
 */
void Gpio::toggle() {
    *mPort ^= mPinBit;
}
/*
 * Getter: returns the pin assigned to object
 * Not used for the program, but could be used in other projects
 */
uint8_t Gpio::getPin() const{
    return pin;
}
/*
 * Returns the state of the pin. Mainly used for pins configured as inputs
 */
bool Gpio::read() const {
    if(pin <=7) {
        return PIND & mPinBit;
    } else {
        return PINB & mPinBit;
    }
}