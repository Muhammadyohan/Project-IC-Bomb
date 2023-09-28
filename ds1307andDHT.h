#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <DHT.h>
#include "tm1637.h"

//define pin and type for dht11
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//define modify mode of clock
#define IDLE_MODE 0
#define INCREASE_MODE 1
#define DECREASE_MODE 2

//declare functions
void DISP_CLOCK();
void DISP_TEMP();
void DISP_CLOCK_TEMP();
void MOD_CLOCK(uint8_t modeSel);
void MOD_HOUR(uint8_t mode);
void MOD_MINUTE(uint8_t mode);

//for DS1307
tmElements_t rtc;    

//display mode check function
//----------------------------**note** ---------------------------------
//                   This function is old function.
//
// void DISP_MODE(uint8_t mode)
// {
//   //mode 1, 2, 3 display check
//   switch(mode)
//   {
//     case 1:
//       DISP_CLOCK();
//       break;
//     case 2:
//       DISP_TEMP();
//       break;
//     case 3:
//       DISP_CLOCK_TEMP();
//       break;
//     default:
//       break;
//   }
// }

//*************************Clock And Temperature Function*************************
//Variables for DISP_CLOCK_TEMP function
unsigned long currentDispTime = 0;
unsigned long previousDispTime = 0;
bool dispClkMode = true;
bool dispTempMode = false;
int mUnit;
int mTen;
int hUnit;
int hTen;
int tUnit;
int tTen;

//clock and temperature display function 
void DISP_CLOCK_TEMP()
{
  //Clock Display
  if(dispClkMode)
  {
    DISP_CLOCK();
    currentDispTime = millis();

    //After 5 seconds Clock Display. Display Mode will change to Temperature Display Mode
    if(currentDispTime - previousDispTime > 5000)
    {
      previousDispTime = millis();
      dispClkMode = false;
      dispTempMode = true;
      tm.clearDisplay();  //Clear tm1637's 7-segment led display
    }
  }
  //Temperature Display
  if(dispTempMode)
  {
    DISP_TEMP();
    currentDispTime = millis();

    //After 3 seconds Temperature Display. Display Mode will change to Clock Display Mode
    if(currentDispTime - previousDispTime > 3000)
    {
      previousDispTime = millis();
      dispClkMode = true;
      dispTempMode = false;
      tm.clearDisplay();  //Clear tm1637's 7-segment led display
    }
  }
}

//Clock display function 
//Variables for Blinking Point
bool blink_point = false;
unsigned long blinkPointPreviousTime = 0;
void DISP_CLOCK()
{
  //split tens and units of hour and minute
  mUnit = rtc.Minute % 10;
  mTen = rtc.Minute / 10;
  hUnit = rtc.Hour % 10;
  hTen = rtc.Hour / 10;

  //read RTC
  if (RTC.read(rtc)) {
    //clock display use tm.display(position, character) of tm1637
    tm.display(0, hTen);
    tm.display(1, hUnit);
    tm.display(2, mTen);
    tm.display(3, mUnit);
    //blinking : of clock
    if(millis() - blinkPointPreviousTime > 500)
    {
      blinkPointPreviousTime = millis();
      if(blink_point)
      {
        blink_point = false;
        tm.point(0);
      }
      else
      {
        blink_point = true;
        tm.point(1);
      }
    }
  } else {
    //if RTC read error
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
    }
    delay(5000);
  }
}

//Temperature display function 
void DISP_TEMP()
{
  //read temperature from dht11
  int temp = dht.readTemperature();
  //split tens and units of temp
  tUnit = temp % 10;
  tTen = temp / 10;

  //temperature display use tm.display(position, character) of tm1637
  tm.display(0, tTen);
  tm.display(1, tUnit);
  tm.point(0);
  tm.display(2, 12);
}

//*************************Modify Clock Function*************************
//Vairables for Clock Modify
bool blink_clock = false;
unsigned long modClkPreviousTime = 0;
//Switching Modify mode of clock function
void MOD_CLOCK(uint8_t modeSel, uint8_t modMode)
{
  switch (modeSel)
  {
  case 0:
    MOD_HOUR(modMode);
    break;
  
  case 1:
    MOD_MINUTE(modMode);
    break;

  default:
    break;
  }
}

//Modify hour function
void MOD_HOUR(uint8_t mode)
{
  //split tens and units of hour
  hUnit = rtc.Hour % 10;
  hTen = rtc.Hour / 10;
  
  switch (mode)
  {
  case IDLE_MODE:
    //Blinking hour of clock
    if(millis() - modClkPreviousTime > 500)
    {
      modClkPreviousTime = millis();
      if(blink_clock)
      {
        blink_clock = false;
        tm.display(0, CLEAR_DISPLAY);
        tm.display(1, CLEAR_DISPLAY);
      }
      else
      {
        blink_clock = true;
        tm.display(0, hTen);
        tm.display(1, hUnit);
      }
    }
    break;
  
  case INCREASE_MODE:
    rtc.Hour += 1;
    if(rtc.Hour > 23)
      rtc.Hour = 0;
    blink_clock = false;
    tm.display(0, hTen);
    tm.display(1, hUnit);
    break;

  case DECREASE_MODE:
    rtc.Hour -= 1;
    if(rtc.Hour == 255)
      rtc.Hour = 23;
    blink_clock = false;
    tm.display(0, hTen);
    tm.display(1, hUnit);
    break;

  default:
    break;
  }
}

void MOD_MINUTE(uint8_t mode)
{
  //split tens and units of minute
  mUnit = rtc.Minute % 10;
  mTen = rtc.Minute / 10;

  switch (mode)
  {
  case IDLE_MODE:
    //Blinking hour of clock
    if(millis() - modClkPreviousTime > 500)
    {
      modClkPreviousTime = millis();
      if(blink_clock)
      {
        blink_clock = false;
        tm.display(2, CLEAR_DISPLAY);
        tm.display(3, CLEAR_DISPLAY);
      }
      else
      {
        blink_clock = true;
        tm.display(2, mTen);
        tm.display(3, mUnit);
      }
    }
    break;
  
  case INCREASE_MODE:
    rtc.Minute += 1;
    if(rtc.Minute > 59)
      rtc.Minute = 0;
    blink_clock = false;
    tm.display(2, mTen);
    tm.display(3, mUnit);
    break;

  case DECREASE_MODE:
    rtc.Minute -= 1;
    if(rtc.Minute == 255)
      rtc.Minute = 59;
    blink_clock = false;
    tm.display(2, mTen);
    tm.display(3, mUnit);
    break;

  default:
    break;
  }
}