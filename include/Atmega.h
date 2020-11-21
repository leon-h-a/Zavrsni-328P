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
        string pinSignal;
    };
public:
    vector<Pin> allPins;
    Pin PSWM1   {18, INPUT, 0, "pinSwitchMonitor_1", "ANALOG"};
    Pin PSWM2   {19, INPUT, 0, "pinSwitchMonitor_2", "ANALOG"};
    Pin PA1     {24, INPUT, 0, "pinAmmeter_1", "ANALOG"};
    Pin PA2     {25, INPUT, 0, "pinAmmeter_2", "ANALOG"};
    Pin PR1     {5, OUTPUT, 0, "pinRelay_1", "DIGITAL"}; // todo: vrati na 14
    Pin PR2     {13, OUTPUT, 0, "pinRelay_2", "DIGITAL"};
    Pin PS      {4, INPUT, 0, "pinSensor", "ANALOG"};
    Pin PPMW1   {15, OUTPUT, 0, "pinPmw_1", "ANALOG"};
    Pin PPMW2   {16, OUTPUT, 0, "pinPmw_2", "ANALOG"};
    Pin PP1     {27, INPUT, 0, "pinPot_1", "ANALOG"};
    Pin PP2     {28, INPUT, 0, "pinPot_2", "ANALOG"};

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
            for(Pin& pin: *&allPins) { // todo mozda maknut &* svugdje
                if (pin.id == keyValue.key().c_str()){
                    pin.currentValue = keyValue.value().as<int>();
                    break; // todo: ovo ce mozda trebati maknuti
                }
            }
        }
//        updateOutputPins();
    }

    void updateOutputPins(){
        for(const Pin& pin: *&allPins) {
            if (pin.currentValue == 1 && pin.pinSignal == "DIGITAL"){
                digitalWrite(pin.pinNumber, HIGH);
            }
            else if (pin.currentValue == 0 && pin.pinSignal == "DIGITAL"){
                digitalWrite(pin.pinNumber, LOW);
            }
            else if (pin.pinMode == OUTPUT && pin.pinSignal == "ANALOG"){
                analogWrite(pin.pinNumber, pin.currentValue); // Analog write [OFF-ON] = 0-255
            }
            else{
                continue;
            }
        }
    }

    void updateInputPins(){
        for(Pin& pin: *&allPins) {
            if (pin.pinSignal == "DIGITAL" && pin.pinMode == INPUT){
                pin.currentValue = (int) digitalRead(pin.pinNumber);
            }
            else if (pin.pinSignal == "ANALOG" && pin.pinMode == INPUT){
                pin.currentValue = (int) analogRead(pin.pinNumber);
            }
        }
    }

    void setPinModes() {
        for (auto &Pin : allPins) {
            pinMode(Pin.pinNumber, Pin.pinMode);
        }
    }

    void handleRequest(String message) {
        StaticJsonDocument<60> doc; // todo: ovo treba izracunati kako spada
        if (DeserializationError err = deserializeJson(doc, message)) {
            Serial.print("deserializeJson() failed with code: ");
            Serial.println(err.c_str());
        }
        if (doc["type"] == "requestCommand") {
            handleCommandRequest(doc.as<JsonObject>());
        }
        else if (doc["type"] == "dataRequest") {
            handleDataRequest();
        }
        else {
            Serial.println("Wrong request type");
        }
    }

    void handleDataRequest() {
        updateInputPins();
        StaticJsonDocument<60> doc; // todo: ovo treba izracunati kako spada
        Serial.print("sim");
        for(Pin& pin: allPins) {
            doc[pin.id.c_str()] = pin.currentValue;
        }
        serializeJson(doc, Serial);
    }
};
#endif //ZAVRSNI_328P_ATMEGA_H