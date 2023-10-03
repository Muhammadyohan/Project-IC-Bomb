#define HOUR 0
#define MINUTE 1
#include "read_switch.h"

uint8_t clock_alarming = 0;

//Variables for storing Hour and Minute of Clock Alarm
uint8_t hour_clk_alarm = 0;
uint8_t minute_clk_alarm = 0;

uint8_t CLOCK_ALARM_READ(uint8_t sel);
void CLOCK_ALARM_WRITE(uint8_t sel, uint8_t val);
uint8_t CLOCK_ALARM_CHECK_AND_HANDLE();

uint8_t CLOCK_ALARM_READ(uint8_t sel) {
  switch (sel) {
    case HOUR: return hour_clk_alarm; break;
    case MINUTE: return minute_clk_alarm; break;
    default: break;
  }
}

void CLOCK_ALARM_WRITE(uint8_t sel, uint8_t val) {
  switch (sel) {
    case HOUR: hour_clk_alarm = val; break;
    case MINUTE: minute_clk_alarm = val; break;
    default: break;
  }
}

uint8_t CLOCK_ALARM_CHECK_AND_HANDLE() {
  //read RTC
  if (RTC.read(rtc)) {  
    //Clock alarm check
    if (rtc.Minute == minute_clk_alarm && rtc.Hour == hour_clk_alarm && rtc.Second == 0) 
      clock_alarming = 1;
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

  //handle clock alarm
  if (clock_alarming) {
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
    
    Serial.println("CLock Alarm!");
    do {
      // buzzMelody();
      checkSw = read_switch();
    } while (checkSw == 0);
    clock_alarming = 0;
    Serial.println("Clock cancel Alarming!");
  }
}