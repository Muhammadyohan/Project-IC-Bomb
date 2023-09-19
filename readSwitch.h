//PIN of Switches
#define SW1_PIN 8
#define SW2_PIN 9
#define SW3_PIN 10

//Variable for Read Switch Function
unsigned long swCurrentTime = 0;
unsigned long swPreviousTime = 0;
uint8_t sw1;
uint8_t sw2;
uint8_t sw3;

//Read SW1 SW2 SW3 function
//----------------------------**note** ---------------------------------
//                     not sure it work or not
uint8_t readSwitch() 
{
    sw1 = digitalRead(SW1_PIN);
    sw2 = digitalRead(SW2_PIN);
    sw3 = digitalRead(SW3_PIN);

    if(!sw1 || !sw2 || !sw3)
    {
        delay(20);
        sw1 = digitalRead(SW1_PIN);
        sw2 = digitalRead(SW2_PIN);
        sw3 = digitalRead(SW3_PIN);
        if(!sw1)    //switch 1 preesed
        {
            do
            {
                sw1 = digitalRead(SW1_PIN);
            } while (!sw1);
            delay(20);
            Serial.println("sw1 preesed");
            return 1;
        }
        if(!sw2)    //switch 2 preesed
        {
            do
            {
                sw1 = digitalRead(SW1_PIN);
            } while (!sw2);
            delay(20);
            Serial.println("sw2 preesed");
            return 2;
        }
        if(!sw3)    //switch 3 preesed
        {
            do
            {
                sw1 = digitalRead(SW1_PIN);
            } while (!sw3);
            delay(20);
            Serial.println("sw3 preesed");
            return 3;
        }
    }
    return 0;
}