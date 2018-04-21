/* Temperature Controller for ELBOW Team a.k.a ACES Splint
 *  by julio b. figueroa with contributions from ELBOW TEAM!
 *  For use in ME498 @ UNLV
 *  Copyright 2018
 *
 * If you don't know how to use the code that's fine. Just remember:
 make
 make upload
 make screen   <---- new and improved!
 ls /dev/ttyUSB*
 * to find a list of available ports in case serial monitor screen hijacks it
 * and that's it!
*/
#include <math.h>
#include <Wire.h>               // i2c write transmissions
#include <stdio.h>
#include <stdlib.h>
#include "rgb_lcd.h"            // lcd library for RGB Backlight
#include "unlv.h"
#include "menu.h"

int input;
char junk = ' ';
boolean safetyFlag, loopFlag, stopFlag;

void setup() {
    Serial.begin(9600);          // set up serial baud rate, check makefile
    Serial.println("Please wait 2 seconds");
    delay(2000);        // connect to BT
    lcdStart();
    lcdStartIntro();             // intro text on lcd display
    startIntroduction();          // menu intro text, won't be seen
    delay(10);                   // needed elsewhere (before sensor log?)
    Serial.flush();              // acts as a delay for buffer to TX
}

void loop() {
    menuStart();                         // menu 1,2,3,4 options
    while (Serial.available()==0) {      // wait until buffer has a character
        input = Serial.parseFloat();     // input value, should be integer
        while (Serial.available() > 0) { // head - tail
             junk = Serial.read();       // or junk = s.r()
        }
    }
    /*
    while (Serial.available()==0) {
        input = Serial.read();
    }
    */
    if (junk == 1 && stopFlag != 1) {
        logSequence001();
        stopFlag = 1 ;                      // do not pass go
    }
    else if (junk == 2 && stopFlag != 1 ) {
        Serial.println("you have selected 2");
        stopFlag = 1;                       // do not collect
    }
    else {                                  // either input !int R[1,4] v stopFlag != 0
        stopFlag = 1;
        Serial.println("Please select an integer option 1-2");
        }
    input = 0;
}
