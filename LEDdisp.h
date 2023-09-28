#define bluePin 7
#define redPin 6
#define greenPin 5
#define analogMin 600
#define analogMax 609
#define NUM_COLORS 52
#define delayTime 10

int redValue;
int greenValue;
int blueValue;
int soundSensorPin = A0;
int brightness = 0; 
int colorIndex = 0;
int fadeBright = 10; // ความเร็วของแสง
int colors[NUM_COLORS][3];
bool isMusicPlaying = false;

void anyLED() {
    int i = 0;

    redValue = 255;
    greenValue = 0;
    blueValue = 0;

    do {
        redValue = redValue - 1;
        greenValue = greenValue + 1;

        analogWrite(redPin, redValue);
        analogWrite(greenPin, greenValue);
        delay(delayTime);

        i = i+1;
    } while (i<255);

    redValue = 0;
    greenValue = 255;
    blueValue = 0;
    i = 0;
    do {
        greenValue = greenValue - 1;
        blueValue = blueValue + 1;

        analogWrite(greenPin, greenValue);
        analogWrite(bluePin, blueValue);
        delay(delayTime);

        i = i+1;
    } while (i<255);

    redValue = 0;
    greenValue = 0;
    blueValue = 255;
    i = 0;
    do {
        blueValue = blueValue - 1;
        redValue = redValue + 1;

        analogWrite(bluePin, blueValue);
        analogWrite(redPin, redValue);
        delay(delayTime);

        i = i+1;  
    } while (i<255);
}

void musicLED() {
  int sensorValue = analogRead(soundSensorPin);
  Serial.println(sensorValue);
  if (sensorValue >= analogMax || sensorValue < analogMin) {
    // ความสว่างของ LED ขึ้นอยู่กับค่า sensorValue
    brightness = map(sensorValue, analogMin, analogMax, 0, 255);
    
    for (int i = 0; i < NUM_COLORS; i++) {
    colors[i][0] = map(i, 0, NUM_COLORS - 1, 255, 0); // สีแดง
    colors[i][1] = map(i, 0, NUM_COLORS - 1, 0, 255); // สีเขียว
    colors[i][2] = 128; // สีฟ้า
    }
    
    isMusicPlaying = true;
  } else {
    if (isMusicPlaying) {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      isMusicPlaying = false;
    }
  }
  
  if (isMusicPlaying) {

      int redValue = colors[colorIndex][0];
      int greenValue = colors[colorIndex][1];
      int blueValue = colors[colorIndex][2];

      analogWrite(redPin, redValue);
      analogWrite(greenPin, greenValue);
      analogWrite(bluePin, blueValue);

      colorIndex = (colorIndex + 1) % NUM_COLORS; // เปลี่ยนค่าสีไปสีถัดไป
    
      brightness = brightness - fadeBright;
      if (brightness <= 0 || brightness >= 255) {
        fadeBright = -fadeBright; // เปลี่ยนทิศทางการเพิ่มหรือลดความสว่าง
      }
  }
}