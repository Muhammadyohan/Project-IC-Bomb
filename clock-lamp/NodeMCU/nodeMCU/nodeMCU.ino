#define WHITE_LED 
#define ORANGE_LED
#define VALENTINE_LED
#define DYNAMIC_LED 
#define ALARM_CANCEL
#define LED_BRIGHTNESS
#define 
#define 


/*************************************************************
 This is a simple demo of sending and receiving some data.
 Be sure to check out other examples!
 *************************************************************/
#define BLYNK_TEMPLATE_ID "TMPL6jId1nhQE"
#define BLYNK_TEMPLATE_NAME "MiniProject"
#define BLYNK_AUTH_TOKEN "Cc_0jvVSxL239anKOEkHpKaTdfgwww6i"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CoEIoT";
char pass[] = "iot.coe.psu.ac.th";
BlynkTimer timer;

// Alarm Cancel
BLYNK_WRITE(V4)
{
 int value = param.asInt();
 if (value == 1) {
  digitalWrite(ALARM_CANCEL, HIGH);
 } else {
  digitalWrite(ALARM_CANCEL, LOW);
 }
}

// WHITE LED
BLYNK_WRITE(V5)
{
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(WHITE_LED, HIGH);
  } else {
    digitalWrite(WHITE_LED, LOW);
  }
}

//ORANGE LED
BLYNK_WRITE(V6)
{
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(ORANGE_LED, HIGH);
  } else {
    digitalWrite(ORANGE_LED, LOW);
  }
}

//VALENTINE LED
BLYNK_WRITE(V7)
{
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(VALENTINE_LED, HIGH);
  } else {
    digitalWrite(VALENTINE_LED, LOW);
  }
}

//DYNAMIC LED
BLYNK_WRITE(V8)
{
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(DYNAMIC_LED, HIGH);
  } else {
    digitalWrite(DYNAMIC_LED, LOW);
  }
}

// LED Brightness
BLYNK_WRITE(V9)
{
 int value = param.asInt();
 analogWrite (LED_BRIGHTNESS, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
 // Change Web Link Button message to "Congratulations!"
 Blynk.setProperty(V100,"offImageUrl", 
 "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
 Blynk.setProperty(V100,"onImageUrl", 
 "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
 Blynk.setProperty(V100, "url", 
 "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup()
{
 pinMode(,OUTPUT)
 pinMode
 Serial.begin(115200);
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 // Setup a function to be called every 100 ms 
  timer.setInterval(100L, ReadSW);
}

void loop()
{
 Blynk.run();
 timer.run();
} 
