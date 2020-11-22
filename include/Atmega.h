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
    Pin PSWM1   {18, INPUT, 0, "PSWM1", "A"};
    Pin PSWM2   {19, INPUT, 0, "PSWM2", "A"};
    Pin PA1     {24, INPUT, 0, "PA1", "A"};
    Pin PA2     {25, INPUT, 0, "PA2", "A"};
    Pin PR1     {5, OUTPUT, 0, "PR1", "D"};
    Pin PR2     {13, OUTPUT, 0, "PR2", "D"};
    Pin PS      {4, INPUT, 0, "PS", "A"};
    Pin PPMW1   {15, OUTPUT, 0, "PPMW1", "A"};
    Pin PPMW2   {16, OUTPUT, 0, "PPMW2", "A"};
    Pin PP1     {27, INPUT, 0, "PP1", "A"};
    Pin PP2     {28, INPUT, 0, "PP2", "A"};

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
            for(Pin& pin: allPins) {
                if (pin.id == keyValue.key().c_str()){
                    pin.currentValue = keyValue.value().as<int>();
                    break;
                }
            }
        }
    }

    void updateOutputPins(){
        for(const Pin& pin: allPins) {
            if (pin.currentValue == 1 && pin.pinSignal == "D"){
                digitalWrite(pin.pinNumber, HIGH);
            }
            else if (pin.currentValue == 0 && pin.pinSignal == "D"){
                digitalWrite(pin.pinNumber, LOW);
            }
            else if (pin.pinMode == OUTPUT && pin.pinSignal == "A"){
                analogWrite(pin.pinNumber, pin.currentValue); // Analog write [OFF-ON] = 0-255
            }
            else{
                continue;
            }
        }
    }

    void updateInputPins(){
        for(Pin& pin: allPins) {
            if (pin.pinSignal == "D" && pin.pinMode == INPUT){
                pin.currentValue = (int) digitalRead(pin.pinNumber);
            }
            else if (pin.pinSignal == "A" && pin.pinMode == INPUT){
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
        StaticJsonDocument<60> doc;
        if (DeserializationError err = deserializeJson(doc, message)) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(err.c_str());
        }
        if (doc["type"] == "requestCommand") {
            handleCommandRequest(doc.as<JsonObject>());
        }
        else if (doc["type"] == "dataRequest") {
            handleDataRequest();
        }
        else {
            Serial.println("Wrong req type");
        }
    }

    void handleDataRequest() {
        updateInputPins();
        StaticJsonDocument<60> doc;
        for(Pin& pin: allPins) {
            doc[pin.id.c_str()] = pin.currentValue;
        }
        serializeJson(doc, Serial);
    }
};
#endif //ZAVRSNI_328P_ATMEGA_H