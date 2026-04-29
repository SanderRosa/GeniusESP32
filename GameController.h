#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "SequenceManager.h"
#include "LEDController.h"

enum GameState {
    IDLE,
    SHOWING_SEQUENCE,
    WAITING_INPUT,
    LEVEL_UP,
    WAITING_CONFIRMATION,
    GAME_OVER
};

class GameController {
private:
    SequenceManager& sequence;
    LEDController& led;
    GameState state;
    int userStep;       // Passo atual do jogador na sequência
    unsigned long stateTimer;

public:
    GameController(SequenceManager& seq, LEDController& l);
    void startGame();
    void nextRound();
    void processInput(int value);
    void update();
    GameState getState() const { return state; }
    int getLevel() const { return sequence.getLength(); }
    int getUserStep() const { return userStep; }
    void reset();
};

#endif
