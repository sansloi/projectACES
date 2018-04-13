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
boolean safetyFlag = 0;

void setup() {
    Serial.begin(9600);          // set up serial baud rate, check makefile
    lcdStart();
    lcdStartIntro();             // intro text on lcd display
    menuIntroduction();          // menu intro text, won't be seen
    delay(10);                   // needed elsewhere (before sensor log?)
    Serial.flush();              // should clear the screen
}

void loop() {
    menuStart();                         // menu 1,2,3,4 options
    while (Serial.available()==0) {    // wait until buffer has a character
        input = Serial.parseFloat();     // input value, should be integer
        while (Serial.available() > 0) { // head - tail
             junk = Serial.read();     // or junk = s.r()
        }
    }
    if (input == 1) {
        logSequence001();
            }
    else if (input == 2) {
        Serial.println("you have selected 2");
    }
    else if (input == 3) {
        Serial.println("you have selected 3");
    }
    else if (input == 4) {
        Serial.println("you have selected 4");  // or \n would make a new line
    }
}
