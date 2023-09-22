#include "ds1307andDHT.h"
#include "readSwitch.h"
#include "LEDdisp.h"

//Variables for stroring value from readSwitch()
uint8_t checkSw;
uint8_t swVal;

//Variables for parameter of dispMode()
uint8_t dispModeVal = 1;

void setup() {
  //-------------begin tm1637--------------- 
  tm.init();
  //set brightness of tm1637 led; 0-7
  tm.set(2);

  //pin setup
  pinMode(SW1_PIN, INPUT);
  pinMode(SW2_PIN, INPUT);
  pinMode(SW3_PIN, INPUT);
  pinMode(RED, OUTPUT);
  pinMOde(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  checkSw = readSwitch();
  if (checkSw != 0) //Switch preesed
  {
    swVal = checkSw;  //stored return value of readSwitch()
    
    switch (swVal)  //check if which switch is preesed
    {
    //if switch 1 preesed
    //change display mode
    case 1:
      dispModeVal += 1;
      if(dispModeVal > 3)
        dispModeVal = 1;
      Serial.print("display mode = ");
      Serial.println(dispModeVal);
      tm.clearDisplay();  //clear tm1637's 7-segment led display before change to other display mode
      break;

    case 2:
      break;

    case 3:
      break;

    default:
      break;
    }
  }
  dispMode(dispModeVal);
}