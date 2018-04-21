// arduino won't accept cin or cout..
//
#include <stdio.h>
#include <stdlib.h>

char junk = ' ';
long temps; // [ms]

void setup() {
     Serial.begin(9600);
     Serial.println("hello world");
     Serial.print("To begin, press an option from the menu below");
     Serial.print(" ");
     Serial.flush();
}

void loop() {
    Serial.println("To begin program 1 ENTER 1");
    Serial.println("To begin program 2 ENTER 2");

    while(Serial.available() == 1);
    {
        input = Serial.parseFloat();
        while (Serial.available() > 0)
        {
            junk = Serial.read();
        }
    }
    // start-up idea, a magnetic brush where you can turn the polarity +/-
    if (input == 1) {
        Serial.println("You have selected 1");
        Serial.println("input value = ");
        Serial.println(input, DEC);
        Serial.println();
    }
    else if (input == 2) {
        Serial.println("You have selected 2");
        Serial.println("input value = ");
        Serial.println(input, DEC);
        Serial.println();
    }
}
