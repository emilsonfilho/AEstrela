#ifndef AESTRELA_HILLCLIMBING_H
#define AESTRELA_HILLCLIMBING_H
#include "GridProblem.h"
#include "Heuristic.h"

#include <functional>
#include <memory>
#include <utility>

#include "InformedSearchAlgorithm.h"
#include "Node.h"

using namespace std;
using HCStrategy =
    function<shared_ptr<Node<State>>(const shared_ptr<Node<State>>&, const vector<shared_ptr<Node<State>>>&)>;

class HillClimbing : public InformedSearchAlgorithm {
private:
    HCStrategy strategy;
public:
    HillClimbing(GridProblem problem, const Heuristic<State>* heuristic, HCStrategy strategy);

    shared_ptr<Node<State>> search() override;
    vector<shared_ptr<Node<State>>> expand(const shared_ptr<Node<State>>& node);
};

#endif //AESTRELA_HILLCLIMBING_H