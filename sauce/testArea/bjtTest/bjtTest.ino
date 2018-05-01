/* written by Julio B. Figueroa
 * University of Nevada, Las Vegas
 * Howard R. Hughes College of Engineering
 * H-bridge protoype 001
 */
// arduino won't accept cin or cout..
#include <stdio.h>
#include <stdlib.h>

int input;
int bjtPin = 9;
int pinS1 = 2, pinS2 = 3, pinS3 = 4, pinS4 = 5;

// H-bridge prototype
boolean S1 = false, S2 = false, S3 = false, S4 = false;
//      PNP         NPN         PNP         NPN

boolean makeColdFlag, makeHotFlag;

void setup() {
     Serial.begin(9600);
     pinMode(bjtPin, OUTPUT);
}

void shutDown() {
    digitalWrite(pinS1, LOW);
    S1 = false;
    digitalWrite(pinS2, LOW);
    S2 = false;
    digitalWrite(pinS3, LOW);
    S3 = false;
    digitalWrite(pinS4, LOW);
    S4 = false;
    }

void makeCold() {
    if ( S2 == false && S3 == false) {
        S1 = true;
        digitalWrite(pinS1, HIGH);
        S4 = true;
        digitalWrite(pinS4, HIGH);
        delay(5000);
        shutDown();
    }
    else {
        shutDown();
        Serial.print("This should never happen");
    }
}

void makeHot() {
    if ( S1 == false && S3 == false) {
        S2 = true;
        digitalWrite(pinS2, HIGH);
        S3 = true;
        digitalWrite(pinS3, HIGH);
        delay(5000);       // 5 seconds
        shutDown();
    }
    else {
        shutDown();
        Serial.print("This should never happen");
    }
}

// use this for NPN testing
void rampVoltage() {
    for( int x = 0; x<= 255; x+=5) {
        analogWrite(bjtPin,x);
        delay(500);
    }
    for( int x = 255; x >=0; x-=5) {
        analogWrite(bjtPin, x);
        delay(500);
    }
}

void keepOn(int minutes) {
    for( int y = 0; y<= 255; y+=5) {
        analogWrite(bjtPin,y);
        delay(500);
    }
        delay(minutes*60*1000); // you need to self monitor here
        Serial.print("You should have turned it off right NOW!");
}
/*
void keepOn2(int minutes) {
    timeZ = millis();                           // time since program begins
    for (int z = 0; z <- 255; y+=5) {
        analogWrite(bjtPin,z);
        delay(50);
    }
    timeKept = millis()
*/

void onOffMake() {
    //analogWrite(bjtPin, 127); //  half ramp
    digitalWrite(bjtPin, HIGH);
    delay(2000);
    digitalWrite(bjtPin, LOW);
    //analogWrite(bjtPin,0);
    delay(2000);
}

void loop() {
    //rampVoltage();
    keepOn(10);
/*
    delay(1000);
    makeCold();
    shutDown();
    delay(1000);
    makeHot();
    shutDown();
    delay(5000);
*/
}
