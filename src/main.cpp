#include <Arduino.h>
byte incomingByte;

void setup() {
    Serial.begin(9600);
//    while (!Serial) {
//        ; // wait for serial port to connect. Needed for Native USB only
//    }
}

void loop() {
    Serial.write(1);
    delay(700);
    }
//    if (Serial.available() > 0) {
//        // read the incoming byte:
//        incomingByte = Serial.read();
//        Serial.print("I received: ");
//        Serial.println(incomingByte, BIN);
//        Serial.print("Or in DEC: ");
//        Serial.println(incomingByte, DEC);
//    }
//    else {
//        Serial.print("Nista\n");
//        delay(1000);
//    }