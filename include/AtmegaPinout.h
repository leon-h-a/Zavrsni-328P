#ifndef ZAVRSNI_328P_ATMEGAPINOUT_H
#define ZAVRSNI_328P_ATMEGAPINOUT_Hž

#include <string>

class PinOut{
public:
    static const int pinRelay_1 = 14;
    static const int pinRelay_2 = 13;
    static const int pinPmw_1 = 15;
    static const int pinPmw_2 = 16;
    static const int pinSwitchMonitor_1 = 18;
    static const int pinSwitchMonitor_2 = 19;
    static const int pinAmmeter_1 = 24;
    static const int pinAmmeter_2 = 25;
    static const int pinPot_1 = 27;
    static const int pinPot_2 = 28;
    static const int pinSensor = 4;
    static std::string pins[11] = {"pinRelay_1",
                                   "pinRelay_2",
                                   "pinPmw_1",
                                   "pinPmw_2",
                                   "pinSwitchMonitor_1",
                                   "pinSwitchMonitor_2",
                                   "pinAmmeter_1",
                                   "pinAmmeter_2",
                                   "pinPot_1",
                                   "pinPot_2",
                                   "pinSensor"};
};
#endif //ZAVRSNI_328P_ATMEGAPINOUT_H
