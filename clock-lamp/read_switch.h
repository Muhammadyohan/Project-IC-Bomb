#include "pcf8574.h"

#define PCF_ADDR 32

//Variable for Read Switch Function
unsigned long swPreviousTime = 0;

//Read SW1 SW2 SW3 SW4 SW5 and SW6 from PCF8574 function
uint8_t read_switch() {
    uint8_t tmp = PCF8574_read(PCF_ADDR);
    for (int i = 0; i < 6; i++) {
        uint8_t mask = 1 << i;
        if (!(tmp & mask)) {
            if (millis() - swPreviousTime > 50) {
                swPreviousTime = millis();
                do {
                    tmp = PCF8574_read(PCF_ADDR);
                } while (!(tmp & mask));
                return i + 1;
            }
        }
    }
    return 0;
}