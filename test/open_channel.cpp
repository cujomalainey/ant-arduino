/**************************************
 * Open Channel Test
 * 
 * Tests the serial implementation of 
 * the message against the hardware.
 * Tests pass by recieving an OK
 * message from the hardware.
 **************************************/ 
#include <Arduino.h>
#include <unity.h>

#ifdef UNIT_TEST

void setUp(void) {
    // reset nRF
    // purge serial buffer
}

// void tearDown(void) {
// // clean stuff up here
// }

void test_open_channel(void) {
   // setup channel and open it here
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_open_channel);

    UNITY_END();
}

void loop(){} 

#endif // UNIT_TEST
