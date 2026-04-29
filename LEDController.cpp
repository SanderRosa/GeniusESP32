#include "LEDController.h"

LEDController::LEDController(uint8_t ledPin) 
    : pin(ledPin), lastUpdate(0), remainingBlinks(0), ledState(false), interval(300), isErrorMode(false) {}

void LEDController::setup() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void LEDController::blink(int count, unsigned long speed) {
    remainingBlinks = count * 2; // ON and OFF for each blink
    interval = speed;
    lastUpdate = millis();
    ledState = true;
    digitalWrite(pin, HIGH);
    isErrorMode = false;
}

void LEDController::indicateError() {
    isErrorMode = true;
        blink(30, 80); // Sinal de alerta mais longo e marcante para erro
}

void LEDController::indicateSuccess() {
    blink(2, 100); // Two quick flashes for success
}

void LEDController::update() {
    if (remainingBlinks > 0) {
        if (millis() - lastUpdate >= interval) {
            lastUpdate = millis();
            ledState = !ledState;
            digitalWrite(pin, ledState ? HIGH : LOW);
            remainingBlinks--;
            
            if (remainingBlinks == 0) {
                digitalWrite(pin, LOW);
                isErrorMode = false;
            }
        }
    }
}
