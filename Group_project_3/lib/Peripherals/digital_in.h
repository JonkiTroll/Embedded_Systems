#include <stdint.h>

class Digital_in
{
public:
    Digital_in(int pin); //The constructor

    void init();
    void pull_up();
    bool is_hi();
    bool is_lo();

private:
    uint8_t pinMask;

};