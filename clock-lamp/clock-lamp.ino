#include "clock_alarm_modifying.h"
#include "led_disp.h"
#include "EEPROM.h"

void setup() {
  Serial.begin(9600);
  //-------------begin tm1637--------------- 
  tm.init();
  //set brightness of tm1637 led; 0-7
  tm.set(2);

  init_twi_module();

  //------------------Pins setup------------------
  pinMode(soundSensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzPin, OUTPUT);

  //-----------------------------EEPROM-----------------------------
  // EEPROM_clear_all_data();
  // EEPROM_first_write_alarm_time(23, 59);

  tmp_hour_clk_alarm = read_hour_alarm_time_in_EEPROM();
  tmp_minute_clk_alarm = read_minute_alarm_time_in_EEPROM();

  CLOCK_ALARM_WRITE(HOUR, tmp_hour_clk_alarm);
  CLOCK_ALARM_WRITE(MINUTE, tmp_minute_clk_alarm);

  // EEPROM_scan_previous_and_write_alarm_time(23, 59);
  
  // display_all_data_in_EEPROM();
  // Scan_all_data_in_EEPROM();

  // Serial.print("Found Hour = ");
  // Serial.println(tmp_hour_clk_alarm);
  // Serial.print("Found Minute = ");
  // Serial.println(tmp_minute_clk_alarm);
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
          CLOCK_ALARM_WRITE(HOUR, tmp_hour_clk_alarm);
          CLOCK_ALARM_WRITE(MINUTE, tmp_minute_clk_alarm);
          EEPROM_scan_previous_and_write_alarm_time(tmp_hour_clk_alarm, tmp_minute_clk_alarm);
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
        else if (isModClkAlarmMode) MOD_CLOCK_ALARM(modModeSel, INCREASE_MODE);
        else defaultLED();
        break;

      case 6: //Decrease Number Button when on Clock Modifying 
        if (isModClkMode) MOD_CLOCK(modModeSel, DECREASE_MODE);
        else if (isModClkAlarmMode) MOD_CLOCK_ALARM(modModeSel, DECREASE_MODE);
        else isMusicLEDEnabled = !isMusicLEDEnabled;
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
    DISP_CLOCK_TEMP(); //Clock and Temperater Display
    CLOCK_ALARM_CHECK_AND_HANDLE(); //Check clock alarm and handle
  }
  if (isMusicLEDEnabled) {
    musicLED();
  } 
}
