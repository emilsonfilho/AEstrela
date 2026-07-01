#ifndef AESTRELA_BESTFIRSTSEARCH_H
#define AESTRELA_BESTFIRSTSEARCH_H

#include <utility>
#include <vector>
#include <memory>
#include <climits>
#include <queue>
#include <functional>

#include "Heuristic.h"
#include "InformedSearchAlgorithm.h"
#include "core/GridProblem.h"
#include "core/Node.h"

using namespace std;

class BestFirstSearch : public InformedSearchAlgorithm {
private:
    function<int(int, int)> evaluationFunction;
    vector<vector<int>> reachedCosts;
public:
    BestFirstSearch(GridProblem  problem, const Heuristic<State>* heuristic, function<int(int, int)> f);

    shared_ptr<Node<State>> search() override;
    vector<shared_ptr<Node<State>>> expand(const shared_ptr<Node<State>> &node) const;
    };

#endif //AESTRELA_BESTFIRSTSEARCH_H