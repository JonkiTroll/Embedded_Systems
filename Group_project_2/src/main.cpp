//
// Created by group 2 on 15/09/21.
//
//



#include "Arduino.h"
#include <util/delay.h>
#include "digital_out.h"

#include <avr/interrupt.h>
#include "encoder.h"
#include "P_controller.h"
#include <stdint.h>

double error_threshold = 0.05;
int period_ms = 10;
uint8_t interrupt_pin = 0;
uint32_t duty = 60;
double Kp = 1.0; //If K_p is = 2.0 and reference speed to 1000, the output oscillates

uint16_t counter = 0;

encoder motor(period_ms, 0);
P_controller speed_controller(Kp, error_threshold, 1200, 100);
Digital_out led(5);

ISR(TIMER1_COMPA_vect){
        PORTB |= (1 << motor.getDRV_PIN2());

}

ISR(TIMER1_COMPB_vect){
        PORTB &= ~(1 << motor.getDRV_PIN2());

}


ISR(INT0_vect)
{
    motor.calc_speed_micros(micros());
    if(motor.get_pulse_counter() > 700 || motor.get_pulse_counter() < -700) {
        motor.set_pulse_counter(0);
        led.toggle(); //should blink at roughly 1 second interval
    }
}

void setup()
{

    //Serial.begin(115200);
    led.init();
    Serial.begin(9600); //Nano speed
    motor.init(PIN2, PIN3, interrupt_pin);
    motor.turn_on();
   // sei(); //Enable global interrupts
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
    Serial.println(motor.get_tau());
    _delay_ms(250);
    motor.turn_off();
    _delay_ms(1000);
*/
    _delay_ms(100);
    int16_t reference_speed = 1000;//(duty*1266)/100;
    int32_t updated_speed = speed_controller.update(reference_speed, motor.get_average());
    motor.update_speed(updated_speed);

    Serial.print("Updated_speed: ");
    Serial.println(updated_speed);
    Serial.println();


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
