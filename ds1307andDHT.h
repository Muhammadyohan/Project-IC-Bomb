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

//Variables for DISP_CLOCK_TEMP function
unsigned long currentDispTime = 0;
unsigned long previousDispTime = 0;
bool dispClkMode = true;
bool dispTempMode = false;


//set clk and dio pin for tm1637
const int tm1637clk = 2;
const int tm1637dio = 3;
TM1637 tm(tm1637clk, tm1637dio);

//for DS1307
tmElements_t rtc;    

//display mode check function
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

//clock display function if display mode = 1
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

//temperature display function if display mode = 2
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

//clock and temperature display function if display mode = 3
//----------------------------**note** ---------------------------------
//          this function doesn't work yet so don't call it
void DISP_CLOCK_TEMP()
{
  //CLock Display Mode
  if(dispClkMode)
  {
    tm.clearDisplay();
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

  //Temperature Display Mode
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