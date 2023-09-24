#define redPin 7
#define greenPin 6
#define bluePin 5
#define analogMin 575
#define analogMax 581


int soundSensorPin = A0;
int redValue;
int greenValue;
int blueValue;
int brightness = 0; 
int fadeBright = 10; //ความเร็วของแสง
unsigned long previousTime = 0;
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

    /*unsigned long currentTime = millis();
    if(currentTime - previousTime >= 200)
    {
      previousTime = currentTime;*/
    
      analogWrite(redPin, redValue);
      analogWrite(greenPin, greenValue);
      analogWrite(bluePin, blueValue);
      
      brightness = brightness + fadeBright;
  
      if (brightness <= 0 || brightness >= 255) {
        fadeBright = ~fadeBright;
      }
      
      // Apply brightness to RGB values
      redValue = 255 - brightness;
      greenValue = brightness;
      blueValue = abs(128 - brightness);
    }
  //}
}