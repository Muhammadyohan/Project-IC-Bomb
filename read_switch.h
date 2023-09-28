#include "pcf8574.h"
//PIN of Switches
#define SW1_PIN 8
#define SW2_PIN 9
#define SW3_PIN 10
#define PCF_ADDR 32

//Variable for Read Switch Function
unsigned long swPreviousTime = 0;
uint8_t sw1;
uint8_t sw2;
uint8_t sw3;
uint8_t sw4;
uint8_t sw5;

//Read SW1 SW2 from PCF8574 function
//----------------------------**note** ---------------------------------
//                    not sure if it work or not
uint8_t read_switch()
{
    uint8_t tmp;
    tmp = PCF8574_read(PCF_ADDR);
    sw1 = tmp & 0x01;
    sw2 = tmp & 0x02;
    sw3 = tmp & 0x04;
    sw4 = tmp & 0x08;
    sw5 = tmp & 0x10;

    if(!sw1 || !sw2 || !sw3 || !sw4 || !sw5)
    {
        if( millis() - swPreviousTime > 50)
        {
            swPreviousTime = millis();
            tmp = PCF8574_read(PCF_ADDR);
            sw1 = tmp & 0x01;
            sw2 = tmp & 0x02;
            sw3 = tmp & 0x04;
            sw4 = tmp & 0x08;
            sw5 = tmp & 0x10;
            if (!sw1)
            {
                do
                {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw1 = tmp & 0x01;
                }
                while(!sw1);
                Serial.println("Swicth 1 preesed");
                return 1;
            }
            if (!sw2)
            {
                do
                {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw2 = tmp & 0x02;
                }
                while(!sw2);
                Serial.println("Swicth 2 preesed");
                return 2;
            }
            if (!sw3)
            {
                do
                {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw3 = tmp & 0x04;
                }
                while(!sw3);
                Serial.println("Swicth 3 preesed");
                return 3;
            }
            if (!sw4)
            {
                do
                {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw4 = tmp & 0x08;
                }
                while(!sw4);
                Serial.println("Swicth 4 preesed");
                return 4;
            }
            if (!sw5)
            {
                do
                {
                    tmp = PCF8574_read(PCF_ADDR);
                    sw5 = tmp & 0x10;
                }
                while(!sw5);
                Serial.println("Swicth 5 preesed");
                return 5;
            }
        }
    }
    return 0;
}

//Read SW1 SW2 function
//----------------------------**note** ---------------------------------
//                    This function is old function
// uint8_t readSwitch() 
// {
//     sw1 = digitalRead(SW1_PIN);
//     sw2 = digitalRead(SW2_PIN);
//     sw3 = digitalRead(SW3_PIN);

//     if(!sw1 || !sw2 || !sw3)
//     {
//         delay(20);
//         sw1 = digitalRead(SW1_PIN);
//         sw2 = digitalRead(SW2_PIN);
//         sw3 = digitalRead(SW3_PIN);
//         if(!sw1)    //switch 1 preesed
//         {
//             do
//             {
//                 sw1 = digitalRead(SW1_PIN);
//             } while (!sw1);
//             delay(20);
//             Serial.println("sw1 preesed");
//             return 1;
//         }
//         if(!sw2)    //switch 2 preesed
//         {
//             do
//             {
//                 sw2 = digitalRead(SW2_PIN);
//             } while (!sw2);
//             delay(20);
//             Serial.println("sw2 preesed");
//             return 2;
//         }
//         if(!sw3)    //switch 3 preesed
//         {
//             do
//             {
//                 sw3 = digitalRead(SW3_PIN);
//             } while (!sw3);
//             delay(20);
//             Serial.println("sw3 preesed");
//             return 3;
//         }
//     }
//     return 0;
// }