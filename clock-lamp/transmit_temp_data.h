#include <SoftwareSerial.h>
const byte rxPin = 10;
const byte txPin = 11;
SoftwareSerial UnoSerial(rxPin, txPin); // RX | TX

void send_data_to_odroidC4 (int temp) {
    UnoSerial.print(temp);
}