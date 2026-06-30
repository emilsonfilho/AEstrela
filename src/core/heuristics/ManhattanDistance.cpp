#include "heuristics/ManhattanDistance.h"

int ManhattanDistance::calculate(const State &current, const State &goal) const {
    return abs(current.x - goal.x) + abs(current.y - goal.y);
}
