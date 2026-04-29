#ifndef SEQUENCE_MANAGER_H
#define SEQUENCE_MANAGER_H

#include <Arduino.h>
#include <vector>

class SequenceManager {
private:
    std::vector<int> sequence;

public:
    SequenceManager();
    void addStep();
    void reset();
    const std::vector<int>& getSequence() const;
    int getLength() const;
    int getStep(int index) const;
};

#endif
