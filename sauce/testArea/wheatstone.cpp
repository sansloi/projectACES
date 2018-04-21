#include <Arduino.h>
#include <math.h>

const int pinNTC1_Vin = A0;
const int pintNTC1_V2 = A1;

double makeBread(float R1, float R2, float R3, int pinNTC1_Vin, \
        int pinNTC1_V2) {
    double AnalogVoltage2 = analogRead(pinNTC1_V2)*(5.0/1023.0);
    double AnalogVoltageIn = analogRead(pinNTC1_Vin)*(5.0/1023.0);



    return 0;
}


