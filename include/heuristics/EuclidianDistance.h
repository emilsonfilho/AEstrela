#ifndef AESTRELA_EUCLIDIANDISTANCE_H
#define AESTRELA_EUCLIDIANDISTANCE_H

#include <cmath>

#include "core/State.h"
#include "heuristics/Heuristic.h"

class EuclidianDistance : public Heuristic<State> {
public:
    int calculate(const State &current, const State &goal) const override;
};

#endif //AESTRELA_EUCLIDIANDISTANCE_H