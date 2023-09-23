#define redPin 7
#define greenPin 6
#define bluePin 5
#define delayTime 10
#define analogMin 570 
#define analogMax 574 
//Test
int soundSensorPin = A0;
int redValue;
int greenValue;
int blueValue;
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

void musicLED(){
  int sensorValue = analogRead(soundSensorPin);
  if (sensorValue >= analogMax || sensorValue <= analogMin) {
    // ความสว่างของ LED ขึ้นอยู่กับค่า sensorValue
    int brightness = map(sensorValue, analogMin, analogMax, 0, 255);
    analogWrite(redPin, brightness);
    analogWrite(greenPin, brightness);
    analogWrite(bluePin, brightness);
    isMusicPlaying = true;

  } else {
    if (isMusicPlaying) {
      // ปิด LED เมื่อเพลงหยุด
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      isMusicPlaying = false;
    }
  }
}