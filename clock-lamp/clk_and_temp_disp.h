#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <DHT11.h>
#include "tm1637.h"
#include "global_variables.h"
#include "transmit_temp_data.h"

//define for modify mode of clock and clock alarm
#define IDLE_MODE 0
#define INCREASE_MODE 1
#define DECREASE_MODE 2
//define pin and type for dht11
#define DHTPIN 4
DHT11 dht11(DHTPIN);

//declare functions
void DISP_CLOCK();
void DISP_TEMP();
void DISP_CLOCK_TEMP();

//for DS1307
tmElements_t rtc;    

//*************************Clock And Temperature Function*************************
//Variables for DISP_CLOCK_TEMP function
unsigned long currentDispTime = 0;
unsigned long previousDispTime = 0;
bool dispClkMode = true;
bool dispTempMode = false;
int mUnit, mTen, hUnit, hTen, tUnit, tTen;

//clock and temperature display function 
void DISP_CLOCK_TEMP() {
  //Clock Display
  if(dispClkMode) {
    DISP_CLOCK();
    currentDispTime = millis();
    //After 5 seconds Clock Display. Display Mode will change to Temperature Display Mode
    if(currentDispTime - previousDispTime > 5000) {
      previousDispTime = millis();
      dispClkMode = false;
      dispTempMode = true;
      tm.point(0);
      tm.clearDisplay();  //Clear tm1637's 7-segment led display
    }
  }

  //Temperature Display
  if(dispTempMode)
  {
    DISP_TEMP();
    currentDispTime = millis();
    //After 2 seconds Temperature Display. Display Mode will change to Clock Display Mode
    if(currentDispTime - previousDispTime > 2000) {
      previousDispTime = millis();
      dispClkMode = true;
      dispTempMode = false;
      tm.point(0);
      tm.clearDisplay();  //Clear tm1637's 7-segment led display
    }
  }
}

//Clock display function 
//Variables for Blinking Point
bool blink_point = false;
unsigned long blinkPointPreviousTime = 0;
void DISP_CLOCK() {
  //read RTC
  if (RTC.read(rtc)) {
    //split tens and units of hour and minute
    mUnit = rtc.Minute % 10;
    mTen = rtc.Minute / 10;
    hUnit = rtc.Hour % 10;
    hTen = rtc.Hour / 10;
    //clock display use tm.display(position, character) of tm1637
    tm.display(0, hTen);
    tm.display(1, hUnit);
    tm.display(2, mTen);
    tm.display(3, mUnit);

    //blinking : of clock
    if(millis() - blinkPointPreviousTime > 500) {
      blinkPointPreviousTime = millis();
      blink_point = !blink_point;
      tm.point(blink_point ? 1 : 0);
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
unsigned long tempReadDelayPreviousTime = 0;
void DISP_TEMP() {
  int temp;
  //read temperature from dht11 (read dealy = 1 sec.)
  if(millis() - tempReadDelayPreviousTime > 1000) {
    tempReadDelayPreviousTime = millis();
    temp = dht11.readTemperature();
    send_data_to_odroidC4(temp);
  }
  if (temp != DHT11::ERROR_CHECKSUM && temp != DHT11::ERROR_TIMEOUT) {
    //split tens and units of temp
    tUnit = temp % 10;
    tTen = temp / 10;

    //temperature display use tm.display(position, character) of tm1637
    tm.display(0, tTen);
    tm.display(1, tUnit);
    tm.display(2, 12);
  } else Serial.println(DHT11::getErrorString(temp));

}