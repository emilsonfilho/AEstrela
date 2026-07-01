#ifndef AESTRELA_INFORMEDSEARCHALGORITHM_H
#define AESTRELA_INFORMEDSEARCHALGORITHM_H
#include "Heuristic.h"
#include "SearchAlgorithm.h"

class InformedSearchAlgorithm : public SearchAlgorithm {
protected:
    const Heuristic<State> *heuristic;

    InformedSearchAlgorithm(GridProblem problem, const Heuristic<State>* heuristic);
};

#endif //AESTRELA_INFORMEDSEARCHALGORITHM_H