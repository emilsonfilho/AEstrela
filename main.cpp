#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "core/GridProblem.h"
#include "algorithms/BestFirstSearch.h"
#include "algorithms/HillClimbing.h"
#include "heuristics/ManhattanDistance.h"

using namespace std;

int main() {
    vector<vector<int>> map(15, vector<int>(15, 1));

    // Alguns obstáculos
    map[1][0] = OBSTACLE;
    map[1][1] = OBSTACLE;
    map[1][2] = OBSTACLE;
    map[1][3] = OBSTACLE;

    const State start(0, 0);
    const State goal(4, 4);

    const GridProblem problem(map, start, goal);
    const ManhattanDistance heuristic;

    BestFirstSearch aStar(problem, &heuristic, [](const int g, const int h) {
        return g + h;
    });

    BestFirstSearch greedy(problem, &heuristic, [](const int g, const int h) {
        return h;
    });

    BestFirstSearch aStarH3(problem, &heuristic, [](const int g, const int h) {
        return g + 3 * h;
    });

    auto strategyDeterministic = [](const shared_ptr<Node<State>>& current, const vector<shared_ptr<Node<State>>>& neighbors) {
        for (auto& neighbor : neighbors) {
            if (neighbor->h < current->h) return neighbor;
        }
        return shared_ptr<Node<State>>(nullptr);
    };

    auto strategySteepest = [](const shared_ptr<Node<State>>& current, const vector<shared_ptr<Node<State>>>& neighbors) {
        shared_ptr<Node<State>> best = nullptr;
        int minH = current->h;
        for (auto& neighbor : neighbors) {
            if (neighbor->h < minH) {
                minH = neighbor->h;
                best = neighbor;
            }
        }
        return best;
    };

    random_device rd;
    mt19937 gen(rd());

    auto strategyStochastic = [&gen](const shared_ptr<Node<State>>& current, const vector<shared_ptr<Node<State>>>& neighbors) {
        vector<shared_ptr<Node<State>>> betters;
        for (auto& n : neighbors) {
            if (n->h < current->h) betters.push_back(n);
        }

        if (betters.empty()) return shared_ptr<Node<State>>(nullptr);

        uniform_int_distribution<size_t> distrib(0, betters.size() - 1);
        return betters[distrib(gen)];
    };

    HillClimbing hcDeterministics(problem, &heuristic, strategyDeterministic);

    const auto solution = hcDeterministics.search();

    if (solution == nullptr) {
        cout << "Nenhum caminho encontrado.\n";
        return 0;
    }

    cout << "Caminho encontrado!\n";
    cout << "Custo total: " << solution->g << "\n";
    cout << "Nos visitados: " << hcDeterministics.getVisitedNodes() << "\n";
    cout << "Nos gerados: " << hcDeterministics.getGeneratedNodes() << "\n\n";

    vector<State> path;

    for (auto current = solution; current != nullptr; current = current->parent) {
        path.push_back(current->state);
    }

    reverse(path.begin(), path.end());

    cout << "Caminho:\n";

    for (const State& s : path) {
        cout << "(" << s.x << ", " << s.y << ")\n";
    }

    return 0;
}