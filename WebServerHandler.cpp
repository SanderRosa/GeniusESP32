#include "WebServerHandler.h"

WebServerHandler::WebServerHandler(GameController& g) : server(80), game(g) {}

void WebServerHandler::setup() {
    server.on("/", [this]() { handleRoot(); });
    server.on("/start", [this]() { handleStart(); });
    server.on("/next", [this]() { handleNext(); });
    server.on("/move", [this]() { handleMove(); });
    server.on("/status", [this]() { handleStatus(); });
    server.begin();
}

void WebServerHandler::handleClient() {
    server.handleClient();
}

void WebServerHandler::handleRoot() {
    server.send_P(200, "text/html", INDEX_HTML);
}

void WebServerHandler::handleStart() {
    game.startGame();
    server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void WebServerHandler::handleNext() {
    game.nextRound();
    server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void WebServerHandler::handleMove() {
    if (server.hasArg("val")) {
        int val = server.arg("val").toInt();
        game.processInput(val);
        server.send(200, "application/json", "{\"status\":\"processed\"}");
    } else {
        server.send(400, "text/plain", "Bad Request");
    }
}

void WebServerHandler::handleStatus() {
    String stateStr;
    switch (game.getState()) {
        case IDLE: stateStr = "IDLE"; break;
        case SHOWING_SEQUENCE: stateStr = "SHOWING_SEQUENCE"; break;
        case WAITING_INPUT: stateStr = "WAITING_INPUT"; break;
        case LEVEL_UP: stateStr = "LEVEL_UP"; break;
        case WAITING_CONFIRMATION: stateStr = "WAITING_CONFIRMATION"; break;
        case GAME_OVER: stateStr = "GAME_OVER"; break;
    }
    
    String json = "{";
    json += "\"level\":" + String(game.getLevel()) + ",";
    json += "\"state\":\"" + stateStr + "\",";
    json += "\"userStep\":" + String(game.getUserStep());
    json += "}";
    server.send(200, "application/json", json);
}
