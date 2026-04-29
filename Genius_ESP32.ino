/**
 * Projeto: Genius no ESP32
 * Jogo Simon Says com interface Web e POO
 */

#include <WiFi.h>
#include "LEDController.h"
#include "SequenceManager.h"
#include "GameController.h"
#include "WebServerHandler.h"

// 🔥 SEU WIFI
const char* ssid = "sander";
const char* password = "uergs262";

// LED
const uint8_t LED_PIN = 2;

// INSTÂNCIAS
LEDController led(LED_PIN);
SequenceManager sequence;
GameController game(sequence, led);
WebServerHandler webServer(game);

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n--- Genius ESP32 ---");

    // LED
    led.setup();

    // WiFi
    Serial.print("Conectando no WiFi: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\n✅ Conectado!");
    Serial.print("📍 IP: ");
    Serial.println(WiFi.localIP());

    // Servidor Web
    webServer.setup();

    led.indicateSuccess();
}

void loop() {
    game.update();
    webServer.handleClient();
    delay(1);
}