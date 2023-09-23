#include "ds1307andDHT.h"
#include "readSwitch.h"
#include "LEDdisp.h"

//************************Global Variables***********************
//Variables for stroring value from readSwitch()
uint8_t checkSw;
uint8_t swVal;
//Variables for parameter of dispMode()
// uint8_t dispModeVal = 1;

void setup() {
  //-------------begin tm1637--------------- 
  tm.init();
  //set brightness of tm1637 led; 0-7
  tm.set(2);

  //------------Pins setup------------------
  //Switch's pins
  pinMode(SW1_PIN, INPUT);
  pinMode(SW2_PIN, INPUT);
  pinMode(SW3_PIN, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(soundSensorPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  checkSw = read_switch();
  if (checkSw != 0) //Switch preesed
  {
    swVal = checkSw;  //stored return value of readSwitch()
    
    switch (swVal)  //check if which switch is preesed
    {
    //if switch 1 preesed
    //change display mode
    case 1:
      // dispModeVal += 1;
      // if(dispModeVal > 3)
      //   dispModeVal = 1;
      // // Serial.print("display mode = ");
      // // Serial.println(dispModeVal);
      // tm.clearDisplay();  //clear tm1637's 7-segment led display before change to other display mode
      break;

    case 2:
      break;

    case 3:
      break;

    default:
      break;
    }
  }
  // DISP_MODE(dispModeVal);
  DISP_CLOCK_TEMP();
}