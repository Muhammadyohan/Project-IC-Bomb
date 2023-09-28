#include "ds1307andDHT.h"
#include "readSwitch.h"
#include "LEDdisp.h"
#include "buzzer.h"

//************************Global Variables***********************
//Variables for stroring value from readSwitch()
uint8_t checkSw;
uint8_t swVal;
//Variables for parameter of dispMode()
// uint8_t dispModeVal = 1;
//---------------------------------------------------------------

//Variables for Clock Modify Mode
bool isModClkMode = false;
uint8_t modModeSel = 1;

void setup() {
  //-------------begin tm1637--------------- 
  tm.init();
  //set brightness of tm1637 led; 0-7
  tm.set(2);

  init_twi_module();

  //------------Pins setup------------------
  //Switch's pins
  pinMode(SW1_PIN, INPUT);
  pinMode(SW2_PIN, INPUT);
  pinMode(SW3_PIN, INPUT);

  pinMode(soundSensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  //************************Switch preesed***********************
  checkSw = read_switch();
  if (checkSw != 0) 
  {
    swVal = checkSw;  //stored return value of readSwitch()
    Serial.print("swVaL = ");
    Serial.println(swVal);
    
    switch (swVal)  //check if which switch is preesed
    {
    //if switch 1 preesed
    //change display mode
    case 1:
      // dispModeVal += 1;
      // if(dispModeVal > 3)
      //   dispModeVal = 1;
      // Serial.print("display mode = ");
      // Serial.println(dispModeVal);
      // tm.clearDisplay();  //clear tm1637's 7-segment led display before change to other display mode
      break;

    //Clock Modify Select Button
    case 2:
      isModClkMode = true;
      mUnit = rtc.Minute % 10;
      mTen = rtc.Minute / 10;
      hUnit = rtc.Hour % 10;
      hTen = rtc.Hour / 10;
      tm.point(1);
      tm.display(0, hTen);
      tm.display(1, hUnit);
      tm.display(2, mTen);
      tm.display(3, mUnit);
      modModeSel += 1;
      if(modModeSel > 1)
        modModeSel = 0;
      break;

    //Save Button
    case 3:
      if(isModClkMode)
      {
        if (RTC.write(rtc))
        {
          isModClkMode = false;
          modModeSel = 1;
        }
        if (isModClkMode)
        {
          Serial.println("DS1307 Communication Error :-{");
          Serial.println("Please check your circuitry");
        }
      }
      break;
    
    //Increase Number Button
    case 4:
      if(isModClkMode)
        MOD_CLOCK(modModeSel, INCREASE_MODE);
      break;

    //Decrease Number Button
    case 5:
      if(isModClkMode)
        MOD_CLOCK(modModeSel, DECREASE_MODE);
      break;
    }
  }

  //************************Clock Display************************
  if(isModClkMode)
    MOD_CLOCK(modModeSel, IDLE_MODE);
  else
    DISP_CLOCK_TEMP();
}