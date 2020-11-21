#ifndef ZAVRSNI_328P_ATMEGA_H
#define ZAVRSNI_328P_ATMEGA_H

#include <map>
#include <string>
#include <vector>
#include <Arduino.h>
#include <ArduinoJson.h>

using namespace std;


class Atmega {
private:
    struct Pin {
        int pinNumber;
        unsigned char pinMode;
        int currentValue;
        string id;
    };
public:
    vector<Pin> allPins;
    Pin PSWM1   {18, INPUT, 0, "pinSwitchMonitor_1"};
    Pin PSWM2   {19, INPUT, 0, "pinSwitchMonitor_2"};
    Pin PA1     {24, INPUT, 0, "pinAmmeter_1"};
    Pin PA2     {25, INPUT, 0, "pinAmmeter_2"};
    Pin PR1     {5, OUTPUT, 0, "pinRelay_1"}; // todo: vrati na 14
    Pin PR2     {13, OUTPUT, 0, "pinRelay_2"};
    Pin PS      {4, INPUT, 0, "pinSensor"};
    Pin PPMW1   {15, OUTPUT, 0, "pinPmw_1"};
    Pin PPMW2   {16, OUTPUT, 0, "pinPmw_2"};
    Pin PP1     {27, INPUT, 0, "pinPot_1"};
    Pin PP2     {28, INPUT, 0, "pinPot_2"};

    Atmega() {
        allPins.push_back(PSWM1);
        allPins.push_back(PSWM2);
        allPins.push_back(PA1);
        allPins.push_back(PA2);
        allPins.push_back(PR1);
        allPins.push_back(PR2);
        allPins.push_back(PS);
        allPins.push_back(PPMW1);
        allPins.push_back(PPMW2);
        allPins.push_back(PP1);
        allPins.push_back(PP2);

    }

    void handleCommandRequest(const JsonObject obj) {
        for (JsonPair keyValue : obj) {
            for(Pin &pin: *&allPins) {
                if (pin.id == keyValue.key().c_str()){
                    pin.currentValue = keyValue.value().as<int>();
                    break;
                }
            }
        }
    }

    void updateOutputPins(){
        for(const Pin& pin: allPins) {
            if (pin.currentValue == 1){
                digitalWrite(pin.pinNumber, HIGH);
            }
            else if (pin.currentValue == 0){
                digitalWrite(pin.pinNumber, LOW);
            }
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