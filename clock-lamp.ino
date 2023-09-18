#include "ds1307andDHT.h"

//PIN of Switches
#define SW1 8
#define SW2 9
#define SW3 10

//Variable for Read Switch Function
int swPreviousTime = 0;
uint8_t sw1 = 1;
uint8_t sw2 = 1;
uint8_t sw3 = 1;
uint8_t valSw;
int checkSw;

void setup() {
  tm.init();
  //set brightness of tm1637 led; 0-7
  tm.set(2);

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  Serial.begin(9600);
}

void loop() {
  dispMode(2);
}

//read switch function
//----------------------------**note** ---------------------------------
//          this function doesn't work yet so don't call it
bool readSwitch() 
{
  sw1 = digitalRead(SW1);
  sw2 = digitalRead(SW2);
  sw3 = digitalRead(SW3);

  if(!sw1 || !sw2 || !sw3)
  {
    if(millis() - swPreviousTime > 50)
    {
      swPreviousTime = millis();
      sw1 = digitalRead(SW1);
      sw2 = digitalRead(SW2);
      sw3 = digitalRead(SW3);
      if(!sw1)
        Serial.println("sw1 preesed");
        valSw = 1;
        return true;
      if(!sw2)
        Serial.println("sw2 preesed");
        valSw = 2;
        return true;
      if(!sw3)
        Serial.println("sw3 preesed");
        valSw = 3;
        return true;
      }
      else
      {
        return false;
      }
  }
  else
  {
    return false;
  }
}