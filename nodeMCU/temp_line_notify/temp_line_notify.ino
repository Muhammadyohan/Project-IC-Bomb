#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>

SoftwareSerial NodeMCU = SoftwareSerial(D1, D2);

#define SSID        "Yohun"      
#define PASSWORD    "yyyyyyyy"     
#define LINE_TOKEN  "Secret Token"  

void setup() {
  NodeMCU.begin(57600);
  Serial.begin(9600); Serial.println();
  Serial.println(LINE.getVersion());

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

  //Get data from Odroid C4
  while(NodeMCU.available()>0) {
    c = NodeMCU.read();
    if(c=='\n') {break;}
    else {temp_data_in += c;}
  }
  if(c=='\n') {
    Serial.print("Temperature = ");
    Serial.println(temp_data_in);

    //Notify every 3 hours
    if (millis() - notifyPreviousTime > 10,800,000) {
      notifyPreviousTime = millis();
      LINE.notify("Temperature = " + temp_data_in + " C");
    }

    //Reset the variable
    c = 0;
    temp_data_in = "";
  }
}

void checkWifi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("WiFi not connected!");
    delay(1000);
  }
}