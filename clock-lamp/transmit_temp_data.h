#include <SoftwareSerial.h>
const byte rxPin = 10;
const byte txPin = 11;
SoftwareSerial UnoSerial(rxPin, txPin); // RX | TX

void send_data_to_odroidC4 (int temp) {
    String str_temp = String(temp);
    UnoSerial.print(str_temp);
}