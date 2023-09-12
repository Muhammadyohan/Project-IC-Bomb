//กรณีใช้ LED ปกติ
#include "TM1638.h"
#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int strobe = 7;
const int clock = 9;
const int data = 8;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  module.setupDisplay(true, 7); // 7 หน้าจอแสดงผล
  module.setLEDs(0); // ปิด LED บนโมดูล TM1638

  dht.begin();
}

void loop() {
  int hUnit = hour(); // อ่านชั่วโมงปัจจุบัน
  float temperature = dht.readTemperature(); // อ่านค่าอุณหภูมิจาก DHT11

  // แสดงค่าอุณหภูมิบน 7-Segment
  char tempStr[5];
  dtostrf(temperature, 4, 1, tempStr); // แปลงให้มี 1 ตำแหน่งทศนิยม
  module.displayText(tempStr, 1, 0); // แสดงข้อความบน 7-Segment

  // ตั้งค่าสี LED ตามเวลา
  if (hUnit >= 6 && hUnit <= 18) {
    analogWrite(LED_R, 255);
    analogWrite(LED_G, 255);
    analogWrite(LED_B, 255);
  } else {
    analogWrite(LED_R, 255);
    analogWrite(LED_G, 165);
    analogWrite(LED_B, 0);
  }

  delay(1000); // รอ 1 วินาที
}


/*
//กรณีใช้ LED WS2812
#include <Adafruit_NeoPixel.h>

#define PIN 2  
#define NUMPIXELS 16  //จำนวน led

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();  // แสดงสีเริ่มต้น
}

void loop() {
  // ตั้งค่าสีแดงทุก LED
  for(int i=0; i<NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));  // สีแดง (R, G, B)
  }
  strip.show();  // แสดงสีที่ตั้งค่า
  delay(1000);  // รอ 1 วินาที

  // ตั้งค่าสีเขียวทุก LED
  for(int i=0; i<NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));  // สีเขียว (R, G, B)
  }
  strip.show();  // แสดงสีที่ตั้งค่า
  delay(1000);  // รอ 1 วินาที
}
*/
