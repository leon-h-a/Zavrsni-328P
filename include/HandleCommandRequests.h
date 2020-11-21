#ifndef ZAVRSNI_328P_HANDLECOMMANDREQUESTS_H
#define ZAVRSNI_328P_HANDLECOMMANDREQUESTS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AtmegaPinout.h>



int handlePinState(int pin, int value);

class Deserialize{
public:
    explicit Deserialize(const char* rawString);
};

Deserialize::Deserialize(const char* rawString) {
    StaticJsonDocument<JSON_OBJECT_SIZE(10)> doc;
    if (DeserializationError err = deserializeJson(doc, rawString)) {
        Serial.print("deserializeJson() failed with code: ");
        Serial.println(err.c_str());
    }
    JsonObject obj = doc.as<JsonObject>();
    String packetType = obj["type"].as<String>();
    if (packetType == "requestControl"){
        // todo: remote mora slat drugacije stringove npr: "relayPinOutput_1" a ne "relay_1"
        handlePinState(Pinout::relayPinOutput_1, obj["relayPinOutput_1"]);
        handlePinState(Pinout::relayPinOutput_2, obj["relayPinOutput_2"]);
        handlePinState(Pinout::pmwPinOutput_1, obj["pmwPinOutput_1"]);
        handlePinState(Pinout::pmwPinOutput_2, obj["pmwPinOutput_2"]);
    }
    else if (packetType == "requestData"){
        // todo
    }
}

int handlePinState(int pin, int wantedValue){

}
#endif //ZAVRSNI_328P_HANDLECOMMANDREQUESTS_H
