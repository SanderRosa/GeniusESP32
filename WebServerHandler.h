#ifndef WEB_SERVER_HANDLER_H
#define WEB_SERVER_HANDLER_H

#include <WebServer.h>
#include "GameController.h"
#include "web_ui.h"

class WebServerHandler {
private:
    WebServer server;
    GameController& game;

public:
    WebServerHandler(GameController& g);
    void setup();
    void handleClient();
    
private:
    void handleRoot();
    void handleStart();
    void handleNext();
    void handleMove();
    void handleStatus();
};

#endif
