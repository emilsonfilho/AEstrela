#include "heuristics/EuclidianDistance.h"

int EuclidianDistance::calculate(const State &current, const State &goal) const {
    const int dx = current.x - goal.x;
    const int dy = current.y - goal.y;

    const double dist = sqrt(dx * dx + dy * dy);
    return static_cast<int>(floor(dist));
}
