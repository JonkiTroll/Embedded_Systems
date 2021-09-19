//
// Created by group 2 on 15/09/21.
//
//



#include "Arduino.h"
#include <util/delay.h>

#include <avr/interrupt.h>
#include "encoder.h"
#include "P_controller.h"
#include "timer_8bit.h"
#define TIMER_INTERVAL_MS 30



encoder motor(10, 20);
P_controller speed_controller(0.5, 0.1);

timer_8bit timer0(TIMER_INTERVAL_MS);

ISR(TIMER1_COMPA_vect){

    PORTB |= (1 << motor.getDRV_PIN2());
}

ISR(TIMER1_COMPB_vect){

    PORTB &= ~(1 << motor.getDRV_PIN2());
}

ISR(TIMER0_COMPA_vect) {
    double updated_speed = speed_controller.update(500, static_cast<double>(motor.get_average()));
    motor.update_speed(updated_speed);
}

ISR(INT0_vect)
{
    motor.calc_speed_micros(micros());
}

void setup()
{

    //Serial.begin(115200);
    Serial.begin(9600); //Nano speed
    motor.init(PIN2, PIN3, 0);
    timer0.init();
    motor.turn_on();
    sei(); //Enable global interrupts
}

void loop()
{
    //_delay_ms(250);
    //speed = motor.calculate_speed();
    //Serial.print("pulses per second: ");
    //Serial.print(motor.getPPS());
    //Serial.print("\n\r");
    //Serial.print("average pulses per second: ");
    //Serial.println(motor.calculate_average());
    
    //Serial.print("\n\r");
    // 1250 - 1288 (1295)
/*
    motor.turn_on();
    _delay_ms(100);
    Serial.println(motor.getTau());
    _delay_ms(250);
    motor.turn_off();
    _delay_ms(1000);
*/
    _delay_ms(100);
    Serial.println(motor.get_average());


}

/*
 *  ARDUINO Format:
 *
 *  int main(){
 *      setup();
 *
 *      while(1){
 *          //Serial check
 *          loop();
 *      }
 *      return 0;
 *  }
 */
