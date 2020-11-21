#ifndef ZAVRSNI_328P_CLASSTEST_H
#define ZAVRSNI_328P_CLASSTEST_H

#include <Arduino.h>

class Atmega{
public:
    Atmega();

    struct Pin{
        int pinNumber;
        unsigned char pinMode;
    };

    Pin relay_1{5, INPUT};

    void writePin() {
        digitalWrite(relay_1.pinNumber, HIGH);
    }
};


#endif //ZAVRSNI_328P_CLASSTEST_H
