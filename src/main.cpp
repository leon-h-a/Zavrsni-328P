#include <Arduino.h>
#include <SoftwareSerial.h>
byte incomingByte;

void setup() {
    Serial.begin(9600);
    pinMode(12, OUTPUT);
}

void loop() {
    while (Serial.available()) {
        incomingByte = Serial.read();
        if (incomingByte == 0b00000001){
            digitalWrite(12, HIGH);
        }
        else if (incomingByte == 0b00000010){
            digitalWrite(12, LOW);
        }
    }
    delay(100);
}