#include "SequenceManager.h"

SequenceManager::SequenceManager() {
    randomSeed(analogRead(0));
}

void SequenceManager::addStep() {
    // Usando esp_random() para garantir aleatoriedade real por hardware na ESP32
    sequence.push_back((esp_random() % 9) + 1); // Números de 1 a 9
}

void SequenceManager::reset() {
    sequence.clear();
}

const std::vector<int>& SequenceManager::getSequence() const {
    return sequence;
}

int SequenceManager::getLength() const {
    return sequence.size();
}

int SequenceManager::getStep(int index) const {
    if (index >= 0 && index < sequence.size()) {
        return sequence[index];
    }
    return -1;
}
