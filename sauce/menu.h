/* Temperature Controller for ELBOW Team a.k.a CORE SPLINT
 * by julio b. figueroa with contributions form ELBOW TEAM!
 * For use by our ELBOW TEAM ME498 class @ UNLV
 * Copyright 2018
 *
 * This file is to store strings and outputs that go to the LCD + serial
 * monitor. Its purpose is to conserve space and save sanity.
*/

// SerialOutTest() is what we're using for testing during phase 4 and 5
// the output should be easy for spreadsheet formatting to deal with [spaces]
//#include <Wire.h>
//#include "rgb_lcd.h"
#ifndef _H_MENU_
#define _H_MENU_

#include <Wire.h>
#include "rgb_lcd.h"

using namespace std;
rgb_lcd lcd;        // using namespace, weird that "using namespace" isn't here

// main CLI Menu for prototype 1, needs to protect against segmentation faults
void menuStart() {
    Serial.println("Enter 1 to run program 1");
    Serial.println("Enter 2 to run program 2");
    Serial.println("Enter 3 to run program 3");
    Serial.println("Enter 4 to run program 4");
    }

void menuIntroduction() {
    Serial.println("Welcome to Team ACES's Prototype Program!");
    Serial.println("UNLV Fall 2018, Acute Cryotherapy Elbow Splint");
    Serial.println("For Quesitons view the Contact Us page on our website");
    Serial.println("Please don't sue us.");
}

// LCC Start
void lcdStart() {
    lcd.begin(16, 2);
    void setRGB(int r, int g, int b);
    lcd.setRGB(005, 015, 135);  // blue
    byte heart[8] = {   // this should make a heart on the lcd
        0b00000,
        0b01010,
        0b11111,
        0b11111,
        0b11111,
        0b01110,
        0b00100,
        0b00000
    };
    lcd.createChar(0, heart);
    return;
}

void lcdStartIntro() {
    lcd.print("legal told us we had to change the project name..");
    return;
}

/*
//void lcdDataValues(float time, float battery, float Ta, float Tc) {
void lcdDataValues(float timeMin) {
    char timeMinChar = timeMin;
    lcd.print("time =");
    lcd.print(timeMinChar);
    return;
}
*/
// how to display time in Min:Sec format on LCD
void lcdDataValues(int timeMin, int timeSec) {
    lcd.setCursor(0,0);
    lcd.print("clk = ");
    lcd.setCursor(7,0);
    lcd.print(timeMin);
    lcd.print(":");
    if (timeSec < 10) {               // to avoid 1 character problem
        lcd.print("0");
        lcd.print(timeSec);
        lcd.setRGB(000,000,255);     // blue
    }
    else {
        lcd.print(timeSec);          // woot! it works!
        lcd.setRGB(255,000,000);     // red
    }
    lcd.setCursor(0,1);
    lcd.write((unsigned char)0);
}
// One of several LCD output functions 
void lcdDataMonitor(int timeMin, int timeSec, float voltageInA, float voltageInB,\
        float voltageInC, float temperature_F) {

    lcd.setCursor(0,0);
    lcd.print("T=");
    lcd.print(temperature_F);
    lcd.print("V1=");
    lcd.print(voltageInA);
    lcd.print("V2=");
    lcd.print(voltageInB);
    lcd.print("V3=");
    lcd.print(voltageInC);
    lcd.print("C=");
    lcd.print(timeMin);
    lcd.print(":");
    if (timeSec< 10) {
        lcd.print("0");
        lcd.print(timeSec);
        lcd.setRGB(000,000,255);
    }
    else {
        lcd.print(timeSec);
        lcd.setRGB(255,000,000);
    }
    return;
}

void serialOut(unsigned long time, int timeMin, int timeSec, float voltageInA, \
        float voltageInB, float voltageInC, float temperature_C, \
        float temperature_F) {
    Serial.print("Time[ms] = ");
    Serial.print(time);
    Serial.print("\t Clock = ");
    Serial.print(timeMin);
    Serial.print(":");
    Serial.print(timeSec);

    Serial.print("\t Voltage1[V] = ");
    Serial.print(voltageInA);
    Serial.print("\t Voltage2[V] =");
    Serial.print(voltageInB);
    Serial.print("\t Voltage3[V] =");
    Serial.print(voltageInC);
    Serial.print("\t Temp.[C] = ");
    Serial.print(temperature_C);
    Serial.print("\t Temp.[F] = ");
    Serial.println(temperature_F);
    return;
}

void serialOut_voltDebug(unsigned long time, int timeMin, int timeSec, \
        float voltageInA, float voltageOutA, float voltageInB, \
        float voltageOutB, float voltageInC, float voltageOutC, \
        float temperature_C, float temperature_F) {
    Serial.print("Time[ms] = ");
    Serial.print(time);
    Serial.print("\t Clock = ");
    Serial.print(timeMin);
    Serial.print(":");
    Serial.print(timeSec);

    Serial.print("\t Voltage1[V] =");
    Serial.print(voltageInA);
    Serial.print("\t vA_out =");
    Serial.print(voltageOutA);

    Serial.print("\t Voltage2[V] =");
    Serial.print(voltageInB);
    Serial.print("\t vB_out =");
    Serial.print(voltageOutB);

    Serial.print("\t Voltage3[V] =");
    Serial.print(voltageInC);
    Serial.print("\t vC_out = ");
    Serial.print(voltageOutC);


    Serial.print("\t Temp.[C] = ");
    Serial.print(temperature_C);
    Serial.print("\t Temp.[F] = ");
    Serial.println(temperature_F);
    return;
}
// the format below is in the format of comma separated values
void CSVout(unsigned long time, float voltageInA, float voltageInB, \
        float voltageInC, float temperature_C) {
//    Serial.println("time [ms], Va_out [V], Vb_out [V], Vc_out [V]");
//    first line above should only print once
    Serial.print(time);
    Serial.print(",");
    Serial.print(voltageInA);
    Serial.print(",");
    Serial.print(voltageInB);
    Serial.print(",");
    Serial.print(voltageInC);
    Serial.print(",");
    Serial.println(temperature_C);

    return;
}

void CSVout2(unsigned long time, float voltageInA, float voltageInB, \
        float voltageInC, float temperature_C, float ntcTempF) {
//    Serial.println("time [ms], Va_out [V], Vb_out [V], Vc_out [V]");
//    first line above should only print once
    Serial.print(time);
    Serial.print(", ");
    Serial.print(voltageInA);
    Serial.print(", ");
    Serial.print(voltageInB);
    Serial.print(", ");
    Serial.print(voltageInC);
    Serial.print(", ");
    Serial.print(temperature_C);
    Serial.print(", ");
    // use whichever variable you need for temp below
    Serial.println(ntcTempF);

    return;
}

void CSVout3(unsigned long time, float voltageInA, float voltageInB, \
        float voltageInC, float temperature_C, float ntcTempF, float quickVoltage2, float quickVoltageIn) {
//    Serial.println("time [ms], Va_out [V], Vb_out [V], Vc_out [V]");
//    first line above should only print once
    Serial.print(time);
    Serial.print(", ");
    Serial.print(voltageInA);
    Serial.print(", ");
    Serial.print(voltageInB);
    Serial.print(", ");
    Serial.print(voltageInC);
    Serial.print(", ");
    Serial.print(temperature_C);
    Serial.print(", ");
    // use whichever variable you need for temp below
    Serial.print(ntcTempF);
    Serial.print(",");
    Serial.print(quickVoltage2);
    Serial.print(",");
    Serial.println(quickVoltageIn);

    return;
}


#endif
