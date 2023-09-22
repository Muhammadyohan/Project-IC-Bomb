#define RED 7
#define GREEN 6
#define BLUE 5
#define delayTime 10
#define SoundSensor A0

int redValue;
int greenValue;
int blueValue;
int SoundSensor = 0;
int threshold = 1023;

void anyLED() {
    int i = 0;

    redValue = 255;
    greenValue = 0;
    blueValue = 0;

    do {
        redValue = redValue - 1;
        greenValue = greenValue + 1;

        analogWrite(RED, redValue);
        analogWrite(GREEN, greenValue);
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

        analogWrite(GREEN, greenValue);
        analogWrite(BLUE, blueValue);
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

        analogWrite(BLUE, blueValue);
        analogWrite(RED, redValue);
        delay(delayTime);

        i = i+1;  
    } while (i<255);
}

void sinLED(){
}

void musicLED(){
    sound = analogRead(SoundSensor);
    if (sound < threshold){
        i = random(0,3)
        if(i = 0){
            analogWrite(RED, 0)
            analogWrite(GREEN, 255)
            analogWrite(BLUE, 1)
        }

        if(i= 1){
            analogWrite(RED,1)
            analogWrite(GREEN, 0)
            analogWrite(BLUE, 1)
        }
        if(i=2){
            analogWrite(RED,0)
            analogWrite(GREEN,1)
            analogWrite(BLUE,0)
        }
        if(i=3){
            analogWrite(RED,1)
            analogWrite(GREEN,0)
            analogWrite(BLUE,255)
        }
        else{
            analogWrite(RED,255)
            analogWrite(GREEN,255)
            analogWrite(BLUE,255)
        }
    }
}



