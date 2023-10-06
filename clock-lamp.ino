#include "clock_alarm_modifying.h"
#include "led_disp.h"
#include "buzzer.h"

void setup() {
  //-------------begin tm1637--------------- 
  tm.init();
  //set brightness of tm1637 led; 0-7
  tm.set(2);

  init_twi_module();

  //------------Pins setup------------------
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
  if (checkSw != 0) {
    swVal = checkSw;  //stored return value of read_switch()
    
    switch (swVal) {  //check if which switch is preesed
      case 1: //Clock Alarm Modify Select Button
        if (edit_allow && !isModClkAlarmMode) 
          setupModClockAlarmDisplay();
        if (edit_allow || isModClkAlarmMode) 
          handleClockAlarmModify();
        break;

      case 2: //Clock Modify Select Button
        if (edit_allow && !isModClkMode) 
          setupModClockDisplay();
        if (edit_allow || isModClkMode) 
          handleClockModify(); 
        break;

      case 3: //Save Button
        if (isModClkMode && RTC.write(rtc)) {
          edit_allow = true;
          isModClkMode = false;
          modModeSel = 1;
        }
        if (isModClkMode) { //Write error
          Serial.println("DS1307 Communication Error :-{");
          Serial.println("Please check your circuitry");
        }
        if (isModClkAlarmMode) {
          CLOCK_ALARM_WRITE(HOUR, temp_hour_clk_alarm);
          CLOCK_ALARM_WRITE(MINUTE, temp_minute_clk_alarm);
          edit_allow = true;
          isModClkAlarmMode = false;
        }
        break;

      case 4: //Cancel Button
        modModeSel = 1;
        edit_allow = true;
        isModClkMode = false; 
        isModClkAlarmMode = false;
        break; 

      case 5: //Increase Number Button when on Clock Modifying 
        if (isModClkMode) MOD_CLOCK(modModeSel, INCREASE_MODE);
        if (isModClkAlarmMode) MOD_CLOCK_ALARM(modModeSel, INCREASE_MODE);
        break;

      case 6: //Decrease Number Button when on Clock Modifying 
        if (isModClkMode) MOD_CLOCK(modModeSel, DECREASE_MODE);
        if (isModClkAlarmMode) MOD_CLOCK_ALARM(modModeSel, DECREASE_MODE);
        break;

      default: break;
    }
  }

  //************************Clock Display************************
  //Clock Modifying and Clock Alarm Modifying Display
  if (!edit_allow) {
    if (isModClkMode) 
      MOD_CLOCK(modModeSel, IDLE_MODE);
    if (isModClkAlarmMode) 
      MOD_CLOCK_ALARM(modModeSel, IDLE_MODE);
  } else {
    DISP_CLOCK_TEMP(); //Clock and Temperatur Display
    CLOCK_ALARM_CHECK_AND_HANDLE(); //Check clock alarm and handle
  }
}