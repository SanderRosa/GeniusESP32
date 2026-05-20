/**
 * Projeto: Genius no ESP32 com Notificação de IP
 */

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> 
#include <ArduinoJson.h>
#include <ESPmDNS.h>               
#include "LEDController.h"
#include "SequenceManager.h"
#include "GameController.h"
#include "WebServerHandler.h"

// 🔥 CONFIGURAÇÕES WIFI
const char* ssid = "sander";      
const char* password = "uergs262"; 

// 🤖 CONFIGURAÇÕES TELEGRAM
const char* botToken = "8751864313:AAFHSh8jiENtt6yWDNYFsV8gsA2k6IArBLw";
const char* chatID = "753817326"; 

// CLIENTE PARA TELEGRAM
WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

// LED E LÓGICA
const uint8_t LED_PIN = 2;
LEDController led(LED_PIN);
SequenceManager sequence;
GameController game(sequence, led);
WebServerHandler webServer(game);

// Variáveis para controle do Bot
unsigned long lastTimeBotRan;
const unsigned long botDelay = 2000; // Verifica novas mensagens a cada 2 segundos

void handleNewMessages(int numNewMessages) {
    for (int i = 0; i < numNewMessages; i++) {
        String chat_id = String(bot.messages[i].chat_id);
        String text = bot.messages[i].text;
        String from_name = bot.messages[i].from_name;

        Serial.print("📩 Mensagem recebida de ID: ");
        Serial.println(chat_id);
        Serial.print("📝 Texto: ");
        Serial.println(text);

        if (text == "/ip" || text == "/status") {
            String ipLocal = WiFi.localIP().toString();
            String reply = "Oi " + from_name + "! 👋\n";
            reply += "📍 Meu IP atual é: " + ipLocal + "\n";
            reply += "🔗 Link: http://" + ipLocal;
            
            if (bot.sendMessage(chat_id, reply, "")) {
                Serial.println("✅ Resposta enviada!");
            } else {
                Serial.println("❌ Erro ao enviar resposta.");
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n--- Genius ESP32 Online ---");

    led.setup();

    // WiFi
    Serial.print("Conectando: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\n✅ Conectado!");
    
    // Sincroniza o relógio
    configTime(0, 0, "pool.ntp.org");
    client.setInsecure();

    // 1. CONFIGURA mDNS
    if (MDNS.begin("genius")) {
        Serial.println("🌐 Nome de rede: http://genius.local");
    }

    // Servidor Web
    webServer.setup();
    led.indicateSuccess();
    
    Serial.println("🤖 Bot pronto! Mande /ip no Telegram.");
}

void loop() {
    game.update();
    webServer.handleClient();

    // Verifica mensagens do Telegram sem travar o jogo
    if (millis() > lastTimeBotRan + botDelay) {
        Serial.print("🔍 Verificando Telegram... ");
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        
        if (numNewMessages > 0) {
            Serial.printf("✅ %d nova(s) mensagem(ns)!\n", numNewMessages);
            handleNewMessages(numNewMessages);
        } else if (numNewMessages == 0) {
            Serial.println("vazio.");
        } else {
            Serial.println("❌ Erro na conexão com o Telegram!");
        }
        
        lastTimeBotRan = millis();
    }
    
    delay(1);
}