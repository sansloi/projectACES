//#include <arduino.h>

char junkn = ' ';
long temps;

void setup() {
    Serial.begin(9600);
    Serial.print("Select an option form the menu below");
    Serial.flush()' // waits for buffer to fully RX, do i need this?
}

void loop() {
    Serial.println("To begin program 1 press 1");
    Serial.println("To begin program 2 press 2");

    while(Serial.available() == 1) {
        input = Serial.parseFloat();
        while (Serial.available() > 0) {          // if something exist in buffer
            junk = Serial.read();
        }
    }

    if (input == 1) {
        Serial.println("input = 1");
    }
    else {
        Serial.println("input != 1");
    }
}
