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
#include "MCP3008.h"            // analog to digital IC header

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

char rx_byte = 0;

void loop() {
    menuStart();                         // menu 1,2,3,4 options

    if (Serial.available() > 0) {      // wait until buffer has a character
        rx_byte = Serial.read();     // input value, should be integer
        if ((rx_byte >= '0') && (rx_byte <= '9')) {
            Serial.print("value received: ");
            Serial.println(rx_byte);
        }
        else {
            Serial.println("NaN");
        }
    }

    /*
    if (input == 1) {
        //logSequence001();                   // use when testing only
        Serial.print("you have selected");
        Serial.println(input);
        stopFlag = 1 ;                      // do not pass go
    }
    //else if (input == 2 && stopFlag != 1 ) {
    else if (input == 2) {
        Serial.print("you have selected 2");
        Serial.println(input);
        stopFlag = 1;                       // do not collect
    }
    else {                                  // either input !int R[1,4] v stopFlag != 0
        stopFlag = 1;
        Serial.println("Please select an integer option 1-2");
        }
    input = 0;
    */
}
