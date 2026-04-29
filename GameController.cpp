#include "GameController.h"

GameController::GameController(SequenceManager& seq, LEDController& l) 
    : sequence(seq), led(l), state(IDLE), userStep(0), stateTimer(0) {}

void GameController::startGame() {
    sequence.reset();
    sequence.addStep();
    state = SHOWING_SEQUENCE;
    userStep = 0;
    stateTimer = millis();
}

void GameController::nextRound() {
    if (state == WAITING_CONFIRMATION) {
        sequence.addStep();
        state = SHOWING_SEQUENCE;
        userStep = 0;
        stateTimer = millis();
    }
}

void GameController::reset() {
    state = IDLE;
    sequence.reset();
    userStep = 0;
}

void GameController::processInput(int value) {
    if (state != WAITING_INPUT) return;

    // Compara o clique atual com o valor correspondente na sequência completa
    if (value == sequence.getStep(userStep)) {
        userStep++;
        
        // Se completou a sequência inteira
        if (userStep >= sequence.getLength()) {
            state = LEVEL_UP;
            stateTimer = millis();
            led.indicateSuccess();
        }
    } else {
        // Errou qualquer número -> Game Over
        state = GAME_OVER;
        led.indicateError();
    }
}

void GameController::update() {
    led.update();

    switch (state) {
        case SHOWING_SEQUENCE:
            if (!led.isBusy()) {
                // Delay de 2 segundos antes de mostrar o NOVO número (gap entre rodadas)
                if (millis() - stateTimer > 2000) {
                    // PISCA APENAS O ÚLTIMO NÚMERO GERADO
                    int lastNumber = sequence.getStep(sequence.getLength() - 1);
                    led.blink(lastNumber, 250);
                    
                    state = WAITING_INPUT;
                    userStep = 0;
                    stateTimer = millis();
                }
            }
            break;

        case LEVEL_UP:
            if (!led.isBusy() && millis() - stateTimer > 800) {
                state = WAITING_CONFIRMATION;
            }
            break;
            
        case WAITING_CONFIRMATION:
        case GAME_OVER:
        case IDLE:
            break;
    }
}
