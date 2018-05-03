/* Temperature controller for ELBOW Team a.k.a CORE Splint
 * by julio b. figueroa with contributions form ELBOW TEAM!
 * for use in ME498 @ UNLV
 * Copyright 2018
 *
 * The purpose of this headerfile is to make the main file easier to read and
 * to hopefully prevent people from stealing our hard work. Let them do their
 * many hours of testing in the machine shop! >_<!
 *
 * That being said, this header file is confidential. Please stop reading it.
 */
#include <Arduino.h>                      // include this for sanity
#include <math.h>
#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>
#include "rgb_lcd.h"
#include "menu.h"                         // repeats killed by def-undef
#include "MCP3008.h"


// REMEMBER TO USE THE NANO V3 LAYOUT!!!!
// reserve A4 and A5 for i2C communication

const int pinVoltSensorA = A5;            // pin to V_out on V.divider circuit
float R_A1 = 176700;
float R_A2 = 80600;

const int pinVoltSensorB = A4;
float R_B1 = 177400;
float R_B2 = 80600;

const int pinVoltSensorC = A3;
float R_C1 = 1000800;
float R_C2 = 97600;

// previous wheatstone allocations
const int pinNTC1_Vin = A1;           // NTC1 Vin to A1
const int pinNTC1_V2 = A2;            // NTC1 V2 to A2

                    //R_A1    R_A2    R_B1    R_B2    R_C1     R_C2
float resist[][3] = {{176700, 80600},{177400, 80600},{1000800, 97600}};
// should I use arrays for this?
/***************************thermresistor values*******************************/
const int pinTempSensor = A0;
float B = 4275;                 // datasheet says this be Ta beta  @ 25C
float R0 = 100000;
float thermResist[][2] = {{4275, 100000}}; // For Beta Model (B, R1)
//double NTC1_ABC[3] = {2.942517*pow(10,-3), -1.1643*pow(10,-4), 1.34663*pow(10,-5)};

/*****************************calculate time***********************************/
double timeMinR;
/***********************Temperature from Beta Model****************************/
//float CelsiusFromThermsistor(int pinTempSensor, float R0, float B) {
float CelsiusFromThermsistor(int pinTempSensor) {
    //int a = analogRead(pinTempSensor);             // why keep it as an a?
    float a = analogRead(pinTempSensor);
//    float R = (1023.0/a)-1.0;
    float R = 1023.0/a-1.0;
//    R = R*R0;                   // as per spec sheet
    float R0 = 100000;
    R = R*R0;               // where R0 = 100k

    float B = 4275;             // declaring it here for test
    // B can range from 4275 to 4299
    //float temperature_C = 1.0/(log(R/R0)/B+1/298.15)-273.15;
    float Ta = 294.4167;         // ambient temperature in [K]
    float temperature_C = (1.0/((log(R/R0)/B)+(1/Ta)))-273.15;

    return temperature_C;
}

float CelsiusToFahrenheit(float temperature_C) {
    float temperature_F = temperature_C*(9.0/5.0)+32.2;
    return temperature_F;
}
/*****************************Calculate Time***********************************/
float calculateTime() {
    unsigned long time = millis();
    double timeMin = time*pow(10,-3);       // time in min
    return timeMin;
}

float calculateMin(double time) {
    float time2 = time/60;
    return time2;
}

float calculateSec(double time) {
    int time3 = (int) time%60;  // lets force time to be an int
    return time3;
}

/*************************LiPo Monitoring System*******************************/
// V_out = V_in * R2/ (R1+R2), so V_in = V_out/k
float voltSourceIn(int pinVoltSensor, float R1, float R2) {
    int voltOut= analogRead(pinVoltSensor)*(5.0/1023.0);    // map that v
    float k = R2/(R1+R2);
    float voltIn = voltOut*k;
    return voltIn;
}
/*
float voltSourceInTest(int pinVoltSensor, float R1, float R2) {
    float voltOut = analogRead(pinVoltSensor)*(5.0/1023.0); // unmap the v
    float voltIn = voltOut/0.2421875;
    return voltIn;
}
*/
float voltSourceOut(int pinVoltSensor) {
    int voltOut = analogRead(pinVoltSensor)*(5.0/1023.0);
    return voltOut;                 // consider putting these 2 in a class
}

// Whatstone Bridge calculations, find Rx of thermsistor Given Vin, V2,
double makeBread(float R1, float R2, float R3, int pinNTC1_Vin, \
        int pinNTC1_V2) {
    double AnalogVoltage2 = analogRead(pinNTC1_V2)*(5.0/1023.0); // unmap
    double AnalogVoltageIn = analogRead(pinNTC1_Vin)*(5.0/1023.0); // unmap
    double AnalogVoltage1 = AnalogVoltageIn * R2/(R1+R2); // save a pin
    double deltaVoltage_21 = AnalogVoltage2 - AnalogVoltage1;
    double LHD = (deltaVoltage_21/AnalogVoltageIn)+(R2/(R1+R2));
    double Rx = (R3*LHD)/(1-LHD);
    // now use Steinhart-Hart values to map Rx to T sensed
    double NTC1_ABC[3] = {2.942517*pow(10,-3), -1.1643*pow(10,-4), 1.34663*pow(10,-5)};
    double Tx_inverse = NTC1_ABC[0]+NTC1_ABC[1]*log(Rx)+ \
                        NTC1_ABC[2]*log(Rx)*log(Rx)*log(Rx);
    double Tx = pow(Tx_inverse, -1);
    return Tx;
}

/* Sequence Algorithms */
void logSequence001 () {
    // Beta model Sub-System
    float temperature_C = CelsiusFromThermsistor(pinTempSensor);
    float temperature_F = CelsiusToFahrenheit(temperature_C);
    // Time Sub-Section
    double time = calculateTime();
    double timeMin = calculateMin(time);
    double timeSec = calculateSec(time);
    // LiPo Monitor Sub-System
    float voltageInA = voltSourceIn(pinVoltSensorA, R_A1, R_A2);
    //float voltageOutA = voltSourceOut(pinVoltSensorB);

    float voltageInB = voltSourceIn(pinVoltSensorB, R_B1, R_B2);
    //float voltageOutB = voltSourceOut(pinVoltSensorB);

    float voltageInC = voltSourceIn(pinVoltSensorC, R_C1, R_C2);
    //float voltageOutC = voltSourceOut(pinVoltSensorC);
    // NTC Whatstone Bridge Sub-System
    double ntcTemp = makeBread(1000.0, 9500.0, 9500.0, pinNTC1_Vin, pinNTC1_V2);
    // measure R values while testing before putting them up here
    double ntcTempC = ntcTemp-273.15;
    double ntcTempF = (ntcTempC-32.2)*(5.0/9.0);
    float quAnalogVoltage2 = analogRead(pinNTC1_V2)*(5.0/1023.0);
    float quAnalogVoltageIn = analogRead(pinNTC1_Vin)*(5.0/1023.0);
    // LCD and Serial Monitor  Sub-System
    lcdDataMonitor(timeMin, timeSec, voltageInA, voltageInB, voltageInC, \
            temperature_F);
    CSVout3(time, voltageInA, voltageInB, voltageInC, temperature_C, \
            ntcTempF, quAnalogVoltage2, quAnalogVoltageIn);
    delay(1000);             // set the sample Rate [ms]
}

/* 2 minutes on, 2 minutes off?, sure */
void seniorDesignDemo() {
    unsigned long timeStart = millis();     // time since last start or restart
    unsigned long timeNow = 0;       // give it a value in the while loop
    unsigned long deltaTime = 0;
    pinMode(2, OUTPUT);
    // example 2*60*1000 is 2 minutes
    while( deltaTime <= 120000) {
        timeNow = millis();
        deltaTime = timeNow - timeStart;     // timeStart won't change in loop
        Serial.println(deltaTime);
        // LCD display time, should i do it here, or call from menu.h?
        lcd.setCursor(0,0);
        lcd.print("Time: ");
        lcd.setCursor(7,0);
        lcd.print(deltaTime/1000);
        // turn MOSFET ch 2 on
        digitalWrite(2, HIGH);
    }
    // reset counter
    // turn MOSFET ch 2 off
    digitalWrite(2, LOW);                   // turn that MOSFET OFF!
    lcd.setCursor(0,0);
    lcd.print("                    ");      // basically just clear the screen
}
