#include "aj-panyayot-pcf8574.h"
//PIN of Switches
#define SW1_PIN 8
#define SW2_PIN 9
#define SW3_PIN 10

//Variable for Read Switch Function
unsigned long swPreviousTime = 0;
uint8_t sw1;
uint8_t sw2;
uint8_t sw3;

//Read SW1 SW2 from PCF8574 function
//----------------------------**note** ---------------------------------
//                    not sure if it work or not
uint8_t read_switch()
{
    uint8_t tmp;
    tmp = PCF8574_read(0);
    sw1 = tmp & 0x01;
    sw2 = tmp & 0x02;

    if(!sw1 || !sw2 || !sw3)
    {
        if( millis() - swPreviousTime > 50)
        {
            swPreviousTime = millis();
            tmp = PCF8574_read(0);
            sw1 = tmp & 0x01;
            sw2 = tmp & 0x02;
            if (!sw1)
            {
                do
                {
                    tmp = PCF8574_read(0);
                    sw1 = tmp & 0x01;
                }
                while(!tmp);
                Serial.println("Swicth 1 preesed");
                return 1;
            }
            if (!sw2)
            {
                do
                {
                    tmp = PCF8574_read(0);
                    sw2 = tmp & 0x02;
                }
                while(!tmp);
                Serial.println("Swicth 2 preesed");
                return 2;
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