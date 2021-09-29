//
// Created by jon on 8/20/21.
//

#include "Gpio.hpp"

Gpio::Gpio(const uint8_t pin, volatile uint8_t *port, const uint8_t IO) : pin(pin), mPort(port){

    mPinBit = (1 << pin); //left bitwies shift to get the bit for the pin

    //Configure the object as either input or output.
    switch (IO) {
        case GPIO_Output:
            *(mPort-1U) |= mPinBit; //set the
        case GPIO_Input:
            *(mPort-1U) &= ~mPinBit;
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
        return *(mPort-2U) & mPinBit;
}