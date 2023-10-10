//Parameter
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
int fadeBright = 10; // Faster Brightness
int colors[NUM_COLORS][3];
int swMode = 0;
uint8_t testSw;

bool isMusicPlaying = false;
bool isMusicLEDEnabled = false;

unsigned long printThresholdTime = 0;
uint8_t readSwForBreak;

// One Tone Color
void defaultLED() {
  swMode++;
  if(swMode>4) swMode = 1;
  switch (swMode) {
    case 1: // White Color
      redValue = 255;
      greenValue = 255;
      blueValue = 255;
      brightness = 255;
      break;

    case 2: // Orange Color
      redValue = 237;
      greenValue = 109;
      blueValue = 0;
      brightness = 200;
      break;

    case 3: // Vallentine Color
      redValue = 191;
      greenValue = 36;
      blueValue = 57;
      brightness = 200;
      break;

    case 4: // Non-led
      redValue = 0;
      blueValue = 0;
      greenValue = 0;
      break;
    default: break;
  }

  analogWrite(redPin, redValue);
  analogWrite(bluePin, blueValue);
  analogWrite(greenPin, greenValue);
}

// RGB FOR MUSIC PUB PUB PUB
uint8_t musicLED() {
    int sensorValue = analogRead(soundSensorPin);
    if(millis() - printThresholdTime > 5000) {
      printThresholdTime = millis();
      Serial.println(sensorValue);
    }
    if (sensorValue >= analogMax || sensorValue < analogMin) {
      
      // Brightness depends on sensorValue
      brightness = map(sensorValue, analogMin, analogMax, 0, 255);

      //Random Value RGB    
       for (int i = 0; i < NUM_COLORS; i++) {
         colors[i][0] = map(i, 0, NUM_COLORS - 1, 255, 0); 
         colors[i][1] = map(i, 0, NUM_COLORS - 1, 0, 255); 
         colors[i][2] = 200;
         //Switch 5 or 6 preessed
         checkSw = read_switch();
         if (checkSw != 0) {
          swVal = checkSw;
          switch (swVal)
          {
            case 5:
              defaultLED();
              isMusicLEDEnabled = false;
              analogWrite(redPin, 0);
              analogWrite(greenPin, 0);
              analogWrite(bluePin, 0);
              return;
              break;

            case 6:
              isMusicLEDEnabled = false;
              analogWrite(redPin, 0);
              analogWrite(greenPin, 0);
              analogWrite(bluePin, 0);
              return;
              break;
            
            default:
              break;
          }
        }  //stored return value of read_switch()
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

        colorIndex = (colorIndex + 1) % NUM_COLORS; // Next Color
        brightness = brightness - fadeBright;
        if (brightness <= 0 || brightness >= 255) {
          fadeBright = -fadeBright; // Invert Bright Value
    }
  }
}



