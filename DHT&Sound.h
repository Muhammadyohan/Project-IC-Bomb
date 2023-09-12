//กรณีใช้ LED ปกติ
#include "DHT.h" 
#define DHTPIN 2 
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE); 

int LED_R = 9;
int LED_G = 10;
int LED_B = 11;

void setup() {
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
} 

void Temp() {
    float h = dht.readHumidity(); 
    float t = dht.readTemperature(); 
    float f = dht.readTemperature(true); 
}

void loop() {
    int hUnit = hour(); // อ่านชั่วโมงปัจจุบัน

    // ตั้งค่าสีเป็นสีขาวในช่วง 6:00 น. - 18:00 น.
    if (hUnitr >= 6 && hUnit <= 18) {
        analogWrite(LED_R, 255);
        analogWrite(LED_G, 255);
        analogWrite(LED_B, 255);
    } else {
        // หากไม่ใช่ช่วงเวลาขาว ให้ตั้งค่าสีเป็นสีส้ม
        analogWrite(LED_R, 255); // สีส้ม (คุณสามารถปรับสีตามความต้องการ)
        analogWrite(LED_G, 165); // สีส้ม (คุณสามารถปรับสีตามความต้องการ)
        analogWrite(LED_B, 0);   // สีส้ม (คุณสามารถปรับสีตามความต้องการ)
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
