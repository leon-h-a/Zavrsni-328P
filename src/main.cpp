#include <Arduino.h>
//#include <string>
//#include <map>
#include <Atmega.h>

using namespace std;

Atmega uC;
String msg;

// Command for remote
/*
 *
 * radi u serial monitoru (Clion)
 * {"type":"requestCommand", "pinRelay_1":1}
 *
 * "{\"type\":\"commandRequest\", \"pinRelay_1\": \"1\"}"
 *
 * original
 * "{\"type\":\"commands\", \"relay_1\": \"none\", \"relay_2\": \"off\", \"pmw_1\": \"-1\", \"pmw_2\": \"100\"}"
 *
 *
 * */

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(100);
    uC.setPinModes();
}

void loop() {
    if (Serial.available()){
        Serial.println("Got something");
        msg = Serial.readString();
        uC.handleRequest(msg);
        uC.updateOutputPins();
    }
    delay(10);
}