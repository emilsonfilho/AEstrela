#ifndef AESTRELA_MANHATTANDISTANCE_H
#define AESTRELA_MANHATTANDISTANCE_H

#include <cmath>

using namespace std;

#include "Heuristic.h"
#include "core/State.h"

class ManhattanDistance : public Heuristic<State> {
public:
    int calculate(const State &current, const State &goal) const override;
};

#endif //AESTRELA_MANHATTANDISTANCE_H