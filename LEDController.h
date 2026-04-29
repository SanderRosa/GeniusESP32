#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

class LEDController {
private:
    uint8_t pin;
    unsigned long lastUpdate;
    int remainingBlinks;
    bool ledState;
    unsigned long interval;
    bool isErrorMode;

public:
    LEDController(uint8_t ledPin);
    void setup();
    void blink(int count, unsigned long speed = 300);
    void indicateError();
    void indicateSuccess();
    void update();
    bool isBusy() const { return remainingBlinks > 0 || isErrorMode; }
};

#endif
