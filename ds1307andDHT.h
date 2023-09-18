#include <TM1637.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include<DHT.h>

//define pin and type for dht11
#define DHTPIN 6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//declare functions
void DISP_CLOCK();
void DISP_TEMP();
void DISP_CLOCK_TEMP();

//use for millis() in function
int pDispClkTime = 0;
int pDispTempTime = 0;

//set clk and dio pin for tm1637
const int tm1637clk = 2;
const int tm1637dio = 3;
TM1637 tm(tm1637clk, tm1637dio);

//for DS1307
tmElements_t rtc;    

//display mode check function
//----------------------------**note** ---------------------------------
//                    this function is temporary
void dispMode(uint8_t mode)
{
  //mode 1, 2, 3 display check
  switch(mode)
  {
    case 1:
      DISP_CLOCK();
      break;
    case 2:
      DISP_TEMP();
      break;
    case 3:
      DISP_CLOCK_TEMP();
      break;
    default:
      break;
  }
}

//clock display function if mode = 1
void DISP_CLOCK()
{
  //split tens and units of hour and minute
  int mUnit = rtc.Minute % 10;
  int mTen = rtc.Minute / 10;
  int hUnit = rtc.Hour % 10;
  int hTen = rtc.Hour / 10;

  //read RTC
  if (RTC.read(rtc)) {
    //clock display use tm.display(position, character) of tm1637
    tm.display(0, hTen);
    tm.display(1, hUnit);
    tm.point(1);
    tm.display(2, mTen);
    tm.display(3, mUnit);
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

//temperature display function if mode = 2
void DISP_TEMP()
{
  //read temperature from dht11
  int temp = dht.readTemperature();
  //split tens and units of temp
  int tUnit = temp % 10;
  int tTen = temp / 10;

  //temperature display use tm.display(position, character) of tm1637
  tm.display(0, tTen);
  tm.display(1, tUnit);
  tm.point(0);
  tm.display(2, 12);
}

//clock and temperature display function if mode = 3
//----------------------------**note** ---------------------------------
//          this function doesn't work yet so don't call it
void DISP_CLOCK_TEMP()
{
  //split tens and units of hour and minute
  int mUnit = rtc.Minute % 10;
  int mTen = rtc.Minute / 10;
  int hUnit = rtc.Hour % 10;
  int hTen = rtc.Hour / 10;

  //read temperature from dht11
  int temp = dht.readTemperature();
  //split tens and units of temperature
  int tUnit = temp % 10;
  int tTen = temp / 10;

  if(millis() - pDispClkTime > 3000)
  {
    pDispClkTime = millis();
    //read RTC
    if (RTC.read(rtc)) {
      //clock display use tm.display(position, character) of tm1637
      tm.display(0, hTen);
      tm.display(1, hUnit);
      tm.point(1);
      tm.display(2, mTen);
      tm.display(3, mUnit);
    } else {
      //if RTC read error
      if (RTC.chipPresent()) {
        Serial.println("The DS1307 is stopped.  Please run the SetTime");
        Serial.println("example to initialize the time and begin running.");
        Serial.println();
      } else {
        Serial.println("DS1307 read error!  Please check the circuitry.");
        Serial.println();
      }
      delay(5000);
    }
  }

  if(millis() - pDispTempTime > 5000)
  {
    //temperature display use tm.display(position, character) of tm1637
    tm.display(0, tTen);
    tm.display(1, tUnit);
    tm.point(0);
    tm.display(2, 12);
  }
}