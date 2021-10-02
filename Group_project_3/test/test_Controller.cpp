//
// Created by jon on 9/30/21.
//

#include "unity.h"
#include <avr/delay.h>
#include "p_controller.h"
#include "pi_controller.h"

void TEST_NORMAL_P_controller() {
    double K_p = 0.5;
    p_controller motor(K_p, -1200.0, 1200.0);
    double result;
    result = motor.update(1000.0, 500.0);
    TEST_ASSERT_EQUAL(500.0*K_p, result);
    result = motor.update(500, 1000.0);
    TEST_ASSERT_EQUAL(-500.0*K_p, result);


}

void TEST_NORMAL_PI_controller() {
    double K_p = 0.5, K_i = 0.01, T = 10;
    pi_controller motor(K_p, K_i, -1200.0, 1200.0, T);
    double result;
    result = motor.update(1000.0, 500.0);
    TEST_ASSERT_EQUAL(275, result);

    //proportional = 250
    //integral = 25
}

void TEST_OVERFLOW_P_controller() {
    double K_p = 1.5;
    p_controller motor(K_p, -1200.0, 1200.0);
    double result;
    result = motor.update(1000.0, 0); //should give 1500 which is larger than limMax.
    TEST_ASSERT_EQUAL(1200.0, result);
    result = motor.update(0, 1000.0); //should give 1500 which is larger than limMax.
    TEST_ASSERT_EQUAL(-1200.0, result);
}


void TEST_CLAMP_INTEGRATOR_PI_controller() {
    double K_p = 0.5, K_i = 1, T = 50;
    pi_controller motor(K_p, K_i, -1200.0, 1200.0, T);
    double result;
    result = motor.update(1000.0, 500.0);
    TEST_ASSERT_EQUAL(1200, result); //goes over limMax
}

int main() {
    _delay_ms(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!

    RUN_TEST(TEST_NORMAL_P_controller);
    RUN_TEST(TEST_NORMAL_PI_controller);
    RUN_TEST(TEST_OVERFLOW_P_controller);
    RUN_TEST(TEST_CLAMP_INTEGRATOR_PI_controller);
    // Add more unit tests here

    UNITY_END(); // stop unit testing

}
