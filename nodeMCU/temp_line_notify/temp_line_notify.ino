#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>

#define SSID        "Yohun"      
#define PASSWORD    "yyyyyyyy"     
#define LINE_TOKEN  "TEkaj9HFTPoPXvpOPfC1hPAUdGTuHdJ0lfFBoomEtZ4"
WiFiClient  client;
int statusCode;

//---------Channel Details---------//
unsigned long counterChannelNumber = 2298963;            // Channel ID
const char * myCounterReadAPIKey = "KTYHSAREQE7LT9HL"; // Read API Key
const int FieldNumber1 = 1;  // The field you wish to read
const int FieldNumber2 = 2;  // The field you wish to read
//-------------------------------//

void setup() {
  Serial.begin(115600); Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("WiFi not connected!");
    delay(1000);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
}

char c;
String temp_data_in;
unsigned long notifyPreviousTime = 0;

void loop() {
  checkWifi();
  //---------------- Channel 1 ----------------//
  long temp = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200) {
    Serial.print("Temperature: ");
    Serial.println(temp);
  } else {
    Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);
  //-------------- End of Channel 1 -------------//
    //Notify every 5 minutes 
  if (millis() - notifyPreviousTime > 300000) {
    String temp_data = String(temp);
    notifyPreviousTime = millis();
    LINE.notify("Temperature = " + temp_data + " C");
  }
}

void checkWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("WiFi not connected!");
    Serial.print("Connecting to ");
    Serial.print(SSID);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(SSID, PASSWORD);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
}