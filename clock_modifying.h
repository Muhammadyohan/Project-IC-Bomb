#include "clk_and_temp_disp.h"

//define modify mode of clock
#define IDLE_MODE 0
#define INCREASE_MODE 1
#define DECREASE_MODE 2

//declare functions
void MOD_CLOCK(uint8_t modeSel);
void MOD_HOUR(uint8_t mode);
void MOD_MINUTE(uint8_t mode);

//*************************Modify Clock Function*************************
//Vairables for Clock Modifying
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
    //Blinking minute of clock
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