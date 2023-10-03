#include "pcf8574.h"
//PIN of Switches
#define PCF_ADDR 32

//Variable for Read Switch Function
unsigned long swPreviousTime = 0;
uint8_t sw1, sw2, sw3, sw4, sw5, sw6;

//Read SW1 SW2 SW3 SW4 SW5 and SW6 from PCF8574 function
uint8_t read_switch()
{
    uint8_t tmp;
    tmp = PCF8574_read(PCF_ADDR);
    sw1 = tmp & 0x01;
    sw2 = tmp & 0x02;
    sw3 = tmp & 0x04;
    sw4 = tmp & 0x08;
    sw5 = tmp & 0x10;
    sw6 = tmp & 0x20;

    if(!sw1 || !sw2 || !sw3 || !sw4 || !sw5 || !sw6) {
        if( millis() - swPreviousTime > 50) {
            swPreviousTime = millis();
            tmp = PCF8574_read(PCF_ADDR);
            sw1 = tmp & 0x01;
            sw2 = tmp & 0x02;
            sw3 = tmp & 0x04;
            sw4 = tmp & 0x08;
            sw5 = tmp & 0x10;
            sw6 = tmp & 0x20;
            if (!sw1) {
                do {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw1 = tmp & 0x01;
                } while(!sw1);
                Serial.println("Swicth 1 preesed");
                return 1;
            }
            if (!sw2) {
                do {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw2 = tmp & 0x02;
                } while(!sw2);
                Serial.println("Swicth 2 preesed");
                return 2;
            }
            if (!sw3) {
                do {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw3 = tmp & 0x04;
                } while(!sw3);
                Serial.println("Swicth 3 preesed");
                return 3;
            }
            if (!sw4) {
                do {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw4 = tmp & 0x08;
                } while(!sw4);
                Serial.println("Swicth 4 preesed");
                return 4;
            }
            if (!sw5) {
                do {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw5 = tmp & 0x10;
                } while(!sw5);
                Serial.println("Swicth 5 preesed");
                return 5;
            }
            if (!sw6) {
                do {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw6 = tmp & 0x20;
                } while(!sw6);
                Serial.println("Swicth 6 preesed");
                return 6;
            }
        }
    }
    return 0;
}