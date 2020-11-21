#ifndef ZAVRSNI_328P_ATMEGA_H
#define ZAVRSNI_328P_ATMEGA_H

#include <map>
#include <string>
#include <vector>
#include <Arduino.h>
#include <ArduinoJson.h>

using namespace std;

struct Pin{
    int pinNumber;
    unsigned char pinMode;
};

class Atmega{
public:
    Atmega();
    bool setPinValue(Pin pinObject, int pinValue);
    void setPinModes();
//    JsonObject deserialize(String msg);
    string getRequestType(String msg);
    void handleCommandRequest(String msg);
    void writeNewValues();
//    void handleDataRequest(String msg);

    vector<Pin> allPins;
    Pin pinSwitchMonitor_1;
    Pin pinSwitchMonitor_2;
    Pin pinAmmeter_1;
    Pin pinAmmeter_2;
    Pin pinRelay_1;
    Pin pinRelay_2;
    Pin pinSensor;
    Pin pinPmw_1;
    Pin pinPmw_2;
    Pin pinPot_1;
    Pin pinPot_2;
};

Atmega::Atmega() {
    pinSwitchMonitor_1.pinNumber = 1,
        pinSwitchMonitor_1.pinMode = INPUT,
    allPins.push_back(pinSwitchMonitor_1);

    pinSwitchMonitor_2.pinNumber = 2,
        pinSwitchMonitor_2.pinMode = INPUT,
    allPins.push_back(pinSwitchMonitor_2);

    pinAmmeter_1.pinNumber = 3,
        pinAmmeter_1.pinMode = INPUT,
    allPins.push_back(pinAmmeter_1);

    pinAmmeter_2.pinNumber = 4,
        pinAmmeter_2.pinMode = INPUT,
    allPins.push_back(pinAmmeter_2);

    pinRelay_1.pinNumber = 5,
        pinRelay_1.pinMode = OUTPUT,
    allPins.push_back(pinRelay_1);

    pinRelay_2.pinNumber = 6,
        pinRelay_2.pinMode = OUTPUT,
    allPins.push_back(pinRelay_2);

    pinSensor.pinNumber = 7,
        pinSensor.pinMode = INPUT,
    allPins.push_back(pinSensor);

    pinPmw_1.pinNumber = 8,
        pinPmw_1.pinMode = OUTPUT,
    allPins.push_back(pinPmw_1);

    pinPmw_2.pinNumber = 9,
        pinPmw_2.pinMode = OUTPUT,
    allPins.push_back(pinPmw_2);

    pinPot_1.pinNumber = 10,
        pinPot_1.pinMode = INPUT,
    allPins.push_back(pinPot_1);

    pinPot_2.pinNumber = 11,
        pinPot_2.pinMode = INPUT,
    allPins.push_back(pinPot_2);
}

void Atmega::setPinModes() {
    for(int i = 0; i < (signed int)allPins.size(); ++i) {
        pinMode(allPins[i].pinNumber, allPins[i].pinMode);
    }
}

bool Atmega::setPinValue(Pin pinObject, int pinValue) {
    digitalWrite(pinObject.pinNumber, pinValue);
    return 1;
}

string Atmega::getRequestType(String msg){
    StaticJsonDocument<120> doc;
    if (DeserializationError err = deserializeJson(doc, msg)) {
        Serial.print("deserializeJson() failed with code: ");
        Serial.println(err.c_str());
    }
    if (doc["type"] == "requestCommand"){
        return "requestCommand";
    }
    else if (doc["type"] == "dataRequest"){
        return "dataRequest";
    }
    else{
        return "Error";
    }
}

void Atmega::handleCommandRequest(String msg){
    StaticJsonDocument<120> doc;
    if (DeserializationError err = deserializeJson(doc, msg)) {
        Serial.print("deserializeJson() failed with code: ");
        Serial.println(err.c_str());
    }
    if (doc["pinRelay_1"] == 1){
        pinRelay_1.currentValue = HIGH;
    }
    else if (doc["pinRelay_1"] == 0){
        pinRelay_1.currentValue = LOW;
    }
}

void Atmega::writeNewValues(){
//    for(unsigned int i = 0; i < allPins.size(); i++) {
//        Serial.print(allPins[i].pinNumber);
//        Serial.print(allPins[i].currentValue);
    digitalWrite(pinRelay_1.pinNumber, pinRelay_1.currentValue);
//    }
}
#endif //ZAVRSNI_328P_ATMEGA_H