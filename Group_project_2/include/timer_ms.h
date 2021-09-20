#include <avr/interrupt.h>
#include <avr/io.h>

class timer_ms {
public:
    explicit timer_ms(uint16_t intervalMs);

    timer_ms(uint16_t intervalMs, uint16_t dutycycle);

    void setDutyCycle(uint16_t duty);

    void init();

    void start();

    void stop();

    uint16_t getInterval();

    uint16_t getDutyCycle();


private:
    uint16_t mTimerInterval;
    uint16_t mDutyCycle;
};