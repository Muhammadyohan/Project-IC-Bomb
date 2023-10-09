#include "clock_modifying.h"
#include "clock_alarm.h"

//declare functions
void MOD_CLOCK_ALARM(uint8_t modeSel ,uint8_t modMode);
void MOD_HOUR_ALARM(uint8_t mode);
void MOD_MINUTE_ALARM(uint8_t mode);
void setupModClockAlarmDisplay();
void handleClockAlarmModify();

//*************************Modify Clock Alarm Function*************************
//Variables for Clock Modifying
bool blink_clock_alarm = false;
unsigned long modClkAlarmPreviousTime = 0;
uint8_t tmp_hour_clk_alarm, tmp_minute_clk_alarm;

//Switching Modify mode of clock alarm function
void MOD_CLOCK_ALARM(uint8_t modeSel, uint8_t modMode) {
  switch (modeSel) {
  case 0: MOD_HOUR_ALARM(modMode); break;
  case 1: MOD_MINUTE_ALARM(modMode); break;
  default: break;
  }
}

//Modify hour of clock alarm function
void MOD_HOUR_ALARM(uint8_t mode) {
  //split tens and units of hour
  hUnit = tmp_hour_clk_alarm % 10;
  hTen = tmp_hour_clk_alarm / 10;
  
  switch (mode) {
    case IDLE_MODE:
      //Blinking hour of clock
      if (millis() - modClkAlarmPreviousTime > 500) {
        modClkAlarmPreviousTime = millis();
        if (blink_clock_alarm) {
          tm.display(0, CLEAR_DISPLAY);
          tm.display(1, CLEAR_DISPLAY);
          blink_clock_alarm = false;
        } else {
          hUnit = tmp_hour_clk_alarm % 10;
          hTen = tmp_hour_clk_alarm / 10;
          tm.display(0, hTen);
          tm.display(1, hUnit);
          blink_clock_alarm = true;
        }
      }
      break;
    
    case INCREASE_MODE:
      tmp_hour_clk_alarm = (tmp_hour_clk_alarm + 1) % 24;
      hUnit = tmp_hour_clk_alarm % 10;
      hTen = tmp_hour_clk_alarm / 10;
      tm.display(0, hTen);
      tm.display(1, hUnit);
      blink_clock_alarm = false;
      break;

    case DECREASE_MODE:
      tmp_hour_clk_alarm = (tmp_hour_clk_alarm + 23) % 24;
      hUnit = tmp_hour_clk_alarm % 10;
      hTen = tmp_hour_clk_alarm / 10;
      tm.display(0, hTen);
      tm.display(1, hUnit);
      blink_clock_alarm = false;
      break;

    default: break;
  }
}

void MOD_MINUTE_ALARM(uint8_t mode) {
  //split tens and units of minute
  mUnit = tmp_minute_clk_alarm % 10;
  mTen = tmp_minute_clk_alarm / 10;

  switch (mode) {
    case IDLE_MODE:
      //Blinking minute of clock
      if (millis() - modClkAlarmPreviousTime > 500) {
        modClkAlarmPreviousTime = millis();
        if (blink_clock_alarm) {
          tm.display(2, CLEAR_DISPLAY);
          tm.display(3, CLEAR_DISPLAY);
          blink_clock_alarm = false;
        } else {
          mUnit = tmp_minute_clk_alarm % 10;
          mTen = tmp_minute_clk_alarm / 10;
          tm.display(2, mTen);
          tm.display(3, mUnit);
          blink_clock_alarm = true;
        }
      }
      break;
    
    case INCREASE_MODE:
      tmp_minute_clk_alarm = (tmp_minute_clk_alarm + 1) % 60;
      mUnit = tmp_minute_clk_alarm % 10;
      mTen = tmp_minute_clk_alarm / 10;
      tm.display(2, mTen);
      tm.display(3, mUnit);
      blink_clock_alarm = false;
      break;

    case DECREASE_MODE:
      tmp_minute_clk_alarm = (tmp_minute_clk_alarm + 59) % 60;
      tm.display(2, mTen);
      tm.display(3, mUnit);
      blink_clock_alarm = false;
      break;

    default: break;
  }
}

//*************************Setup and Handle Clock Alarm*************************
void setupModClockAlarmDisplay() {
  tmp_hour_clk_alarm = CLOCK_ALARM_READ(HOUR);
  tmp_minute_clk_alarm = CLOCK_ALARM_READ(MINUTE);
  //split tens and units of hour and minute
  mUnit = tmp_minute_clk_alarm % 10;
  mTen = tmp_minute_clk_alarm / 10;
  hUnit = tmp_hour_clk_alarm % 10;
  hTen = tmp_hour_clk_alarm / 10;
  tm.point(1);
}

void handleClockAlarmModify() {
  edit_allow = false;
  isModClkAlarmMode = true;
  //Switching Modify Mode between Modify Hour or Modify Minute
  modModeSel = (modModeSel + 1) % 2;
  //Make Number of Hour or Minute Display When Switch to Modify Clock Alarm Hour or Minute
  tm.display(0, hTen);
  tm.display(1, hUnit);
  tm.display(2, mTen);
  tm.display(3, mUnit);
  blink_clock_alarm = true;
}