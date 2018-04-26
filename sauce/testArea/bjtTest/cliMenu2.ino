// arduino won't accept cin or cout..
#include <stdio.h>
#include <stdlib.h>

int input;
int bjtPin = 9;

void setup() {
     Serial.begin(9600);
     pinMode(bjtPin, OUTPUT);
}

void loop() {
    for( int x = 0; x <= 255; x+=5) {
            analogWrite(bjtPin, x);
            delay(50);
            }
    for(int x = 255; x >= 0; x-=5) {
        analogWrite(bjtPin, x);
        delay(50);
    }
}
