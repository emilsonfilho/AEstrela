#include "algorithms/InformedSearchAlgorithm.h"

InformedSearchAlgorithm::InformedSearchAlgorithm(GridProblem problem, const Heuristic<State> *heuristic)
    : SearchAlgorithm(std::move(problem)), heuristic(heuristic) {}
