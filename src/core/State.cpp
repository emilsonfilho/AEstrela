#include "core/State.h"

State::State(): x(0), y(0) {}
State::State(int x, int y): x(x), y(y) {}

bool State::operator==(const State& other) const {
    return x == other.x and y == other.y;
}
bool State::operator!=(const State& other) const {
    return x != other.x or y != other.y;
}