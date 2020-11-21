#include <Arduino.h>
#include <string>
#include <map>
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
    uC.setPinModes();
}

void loop() {
    if(Serial.available()){
        Serial.write("smth");
        msg = Serial.readString();
        if (uC.getRequestType(msg) == "requestCommand"){
            uC.handleCommandRequest(msg);
            uC.writeNewValues();
        }
        else if (uC.getRequestType(msg) == "dataRequest"){
//            uC.handleDataRequest(msg);
        }
    }
}



//    uC.setPinValue(uC.pinRelay_1, 1);
//    delay(1000);
//    uC.setPinValue(uC.pinRelay_1, 0);
//    uC.setPinValue(uC.pinRelay_1, 0);
//    delay(1000);



// todo: stari loop

//    String msg;
//    std::map<std::string, float> deserializedResponse;
//    if (Serial.available()) {
//        msg = Serial.readString();
//        deserializedResponse = fnc::deserializator(msg);
//    }
////        StaticJsonDocument<JSON_OBJECT_SIZE(10)> doc;
////        if (DeserializationError err = deserializeJson(doc, msg)) {
////            Serial.print("deserializeJson() failed with code: ");
////            Serial.println(err.c_str());
////        }
//        JsonObject obj = doc.as<JsonObject>();
//        String packetType = obj["type"].as<String>();
//        if (packetType == "requestControl"){
//            // todo: remote mora slat drugacije stringove npr: "relayPinOutput_1" a ne "relay_1"
//            handlePinState(Pinout::relayPinOutput_1, obj["relayPinOutput_1"]);
//            handlePinState(Pinout::relayPinOutput_2, obj["relayPinOutput_2"]);
//            handlePinState(Pinout::pmwPinOutput_1, obj["pmwPinOutput_1"]);
//            handlePinState(Pinout::pmwPinOutput_2, obj["pmwPinOutput_2"]);
//        }
//    }

//while (Serial.available()) {
//message = Serial.readString();
//messageReady = true;
//if (incomingByte == 0b00000001){
//digitalWrite(12, HIGH);
//Serial.print("Pin 12: ON");
//}
//else if (incomingByte == 0b00000010){
//digitalWrite(12, LOW);
//Serial.print("Pin 12: OFF");
//}
//}
//if (messageReady) {
//DynamicJsonDocument doc(1024);
//DeserializationError error = deserializeJson(doc, message);
//if (error){
//Serial.print(F("deserializeJson() failed: "));
//Serial.print(error.c_str());
//messageReady = false;
//return;
//}
//if (doc["type"] == "request"){
//doc["type"] = "response";
//// Readings from sensor
//doc["temperature"] = (float)random(-5,20);
//doc["humidity"] = (float)random(50,90);
//serializeJson(doc,Serial);
//}
//messageReady = false;
//}