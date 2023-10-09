#include "clk_and_temp_disp.h"

//declare functions
void MOD_CLOCK(uint8_t modeSel, uint8_t modMode);
void MOD_HOUR(uint8_t mode);
void MOD_MINUTE(uint8_t mode);
void setupModClockDisplay();
void handleClockModify();

//*************************Modify Clock Function*************************
//Vairables for Clock Modifying
bool blink_clock = false;
unsigned long modClkPreviousTime = 0;
//Switching Modify mode of clock function
void MOD_CLOCK(uint8_t modeSel, uint8_t modMode) {
  switch (modeSel) {
  case 0: MOD_HOUR(modMode); break;
  case 1: MOD_MINUTE(modMode); break;
  default: break;
  }
}

//Modify hour function
void MOD_HOUR(uint8_t mode) {
  switch (mode) {
    case IDLE_MODE:
      //Blinking hour of clock
      if (millis() - modClkPreviousTime > 500) {
        modClkPreviousTime = millis();
        if (blink_clock) {
          tm.display(0, CLEAR_DISPLAY);
          tm.display(1, CLEAR_DISPLAY);
          blink_clock = false;
        } else {
          //split tens and units of hour
          hUnit = rtc.Hour % 10;
          hTen = rtc.Hour / 10;
          tm.display(0, hTen);
          tm.display(1, hUnit);
          blink_clock = true;
        }
      }
      break;
    
    case INCREASE_MODE:
      rtc.Hour = (rtc.Hour + 1) % 24;
      //split tens and units of hour
      hUnit = rtc.Hour % 10;
      hTen = rtc.Hour / 10;
      tm.display(0, hTen);
      tm.display(1, hUnit);
      blink_clock = false;
      break;

    case DECREASE_MODE:
      rtc.Hour = (rtc.Hour + 23) % 24;
      //split tens and units of hour
      hUnit = rtc.Hour % 10;
      hTen = rtc.Hour / 10;
      tm.display(0, hTen);
      tm.display(1, hUnit);
      blink_clock = false;
      break;

    default: break;
  }
}

void MOD_MINUTE(uint8_t mode) {
  switch (mode) {
    case IDLE_MODE:
      //Blinking minute of clock
      if (millis() - modClkPreviousTime > 500) {
        modClkPreviousTime = millis();
        if (blink_clock) {
          tm.display(2, CLEAR_DISPLAY);
          tm.display(3, CLEAR_DISPLAY);
          blink_clock = false;
        } else {
          //split tens and units of minute
          mUnit = rtc.Minute % 10;
          mTen = rtc.Minute / 10;
          tm.display(2, mTen);
          tm.display(3, mUnit);
          blink_clock = true;
        }
      }
      break;
    
    case INCREASE_MODE:
      rtc.Minute = (rtc.Minute + 1) % 60;
      //split tens and units of minute
      mUnit = rtc.Minute % 10;
      mTen = rtc.Minute / 10;
      tm.display(2, mTen);
      tm.display(3, mUnit);
      blink_clock = false;
      break;

    case DECREASE_MODE:
      rtc.Minute = (rtc.Minute + 59) % 60;
      //split tens and units of minute
      mUnit = rtc.Minute % 10;
      mTen = rtc.Minute / 10;
      tm.display(2, mTen);
      tm.display(3, mUnit);
      blink_clock = false;
      break;

    default: break;
  }
}

//*************************Setup and Handle Clock Alarm*************************
void setupModClockDisplay() {
  //split tens and units of hour
  mUnit = rtc.Minute % 10;
  mTen = rtc.Minute / 10;
  hUnit = rtc.Hour % 10;
  hTen = rtc.Hour / 10;
  tm.display(0, hTen);
  tm.display(1, hUnit);
  tm.display(2, mTen);
  tm.display(3, mUnit);
  tm.point(1);
}

void handleClockModify() {
  edit_allow = false;
  isModClkMode = true;
  //Switching Modify Mode between Modify Hour or Modify Minute
  modModeSel = (modModeSel + 1) % 2;
  //Make Number of Hour or Minute Display When Switch to Modify Hour or Minute
  tm.display(0, hTen);
  tm.display(1, hUnit);
  tm.display(2, mTen);
  tm.display(3, mUnit);
  blink_clock = true;
}