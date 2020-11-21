#ifndef ZAVRSNI_328P_ATMEGA_H
#define ZAVRSNI_328P_ATMEGA_H

#include <map>
#include <string>
#include <vector>
#include <Arduino.h>
#include <ArduinoJson.h>

using namespace std;


class Atmega {
public:
    struct Pin {
        int pinNumber;
        unsigned char pinMode;
    };

    vector<Pin> allPins;
    Pin pinRelay_1{5, OUTPUT};

    Atmega() {
        allPins.push_back(pinRelay_1);
    }


    void handleCommandRequest(const JsonObject obj) {
        if (obj["pinRelay_1"] == 1) {
            digitalWrite(pinRelay_1.pinNumber, HIGH);
        } else if (obj["pinRelay_1"] == 0) {
            digitalWrite(pinRelay_1.pinNumber, LOW);
        }
    }

    void setPinModes() {
        for (auto &Pin : allPins) {
            pinMode(Pin.pinNumber, Pin.pinMode);
        }
    }

    void handleRequest(String message) {
        StaticJsonDocument<60> doc;
        if (DeserializationError err = deserializeJson(doc, message)) {
            Serial.print("deserializeJson() failed with code: ");
            Serial.println(err.c_str());
        }
        if (doc["type"] == "requestCommand") {
            handleCommandRequest(doc.as<JsonObject>());
        } else if (doc["type"] == "dataRequest") {
            Serial.println("dataRequest not implemented");
        }
    }
};

// todo: sa sluzbene dokumentacije
//for (JsonPair p : obj) {
//p.key() // is a JsonString
//p.value() // is a JsonVariant
//}




//void Atmega::writeNewValues(){
//    for(unsigned int i = 0; i < allPins.size(); i++) {
//        Serial.print(allPins[i].pinNumber);
//        Serial.print(allPins[i].currentValue);
//    digitalWrite(pinRelay_1.pinNumber, pinRelay_1.currentValue);
//    }
//}
#endif //ZAVRSNI_328P_ATMEGA_H