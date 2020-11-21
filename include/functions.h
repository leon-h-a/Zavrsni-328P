#ifndef ZAVRSNI_328P_FUNCTIONS_H
#define ZAVRSNI_328P_FUNCTIONS_H

#include <AtmegaPinout.h>
#include <ArduinoJson.h>
#include <string>
#include <map>


float PinStates::readSinglePin(){
    // todo
}

void PinStates::changeSinglePin(){
    // todo
}

float PinStates::readPotentiometers(){
    // todo
}

namespace fnc{
    std::map<std::string, float> deserializator(String rawString) {
        String msg;
        if (Serial.available()) {
            msg = Serial.readString();
            StaticJsonDocument<JSON_OBJECT_SIZE(10)> doc;
            if (DeserializationError err = deserializeJson(doc, msg)) {
                Serial.print("deserializeJson() failed with code: ");
                Serial.println(err.c_str());
            }
            JsonObject obj = doc.as<JsonObject>();
            if (doc["type"] == "requestCommand"){

                for (int i = PinOut::pins.length();;)

                if (doc.containsKey("pinRelay_1"))
                deserialized.insert("123",obj[""]);
            }
        }
    }
}

#endif //ZAVRSNI_328P_FUNCTIONS_H

//std::map<std::string, float> deserialized;
//std::map<int, float> deserializator(char* rawString);
//
//class PinStates{
//public:
//    PinStates();
//    static int pinSwitchMonitor_1;
//    static int pinSwitchMonitor_2;
//    static int pinAmmmeter_1;
//    static int pinAmmmeter_2;
//    static int pinRelay_1;
//    static int pinRelay_2;
//    static int pinSensor;
//    static int pinPmw_1;
//    static int pinPwm_2;
//    static int pinPot_1;
//    static int pinPot_2;
//
//    float readSinglePin();
//    float readPotentiometers();
//    void changeSinglePin();
//};
//
//PinStates::PinStates() {
//    pinSwitchMonitor_1 = PinOut::pinSwitchMonitor_1;
//    pinSwitchMonitor_2 = PinOut::pinSwitchMonitor_2;
//    pinAmmmeter_1 = PinOut::pinAmmeter_1;
//    pinAmmmeter_2 = PinOut::pinAmmeter_2;
//    pinRelay_1 = PinOut::pinRelay_1;
//    pinRelay_2 = PinOut::pinRelay_2;
//    pinSensor = PinOut::pinSensor;
//    pinPmw_1 = PinOut::pinPmw_1;
//    pinPwm_2 = PinOut::pinPmw_1;
//    pinPot_1 = PinOut::pinPot_1;
//    pinPot_2 = PinOut::pinPot_2;
//}
