//Variables for stroring value from readSwitch()
uint8_t checkSw, swVal;
//Variables for Clock Modify Mode and Clock Alarm Modify Mode
bool edit_allow = true;
bool isModClkMode = false;
bool isModClkAlarmMode = false;
uint8_t modModeSel = 1;

//Variables for print test
unsigned long testPrintPreviousTime = 0;