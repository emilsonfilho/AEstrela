#include <iostream>
#include <vector>
#include <random>

#include "core/GridProblem.h"
#include "algorithms/BestFirstSearch.h"
#include "algorithms/HillClimbing.h"
#include "heuristics/ManhattanDistance.h"
#include "utils/Map.h"
#include "utils/PathBuilder.h"

#ifdef _WIN32
#include <windows.h>
void enableAnsiColors() {
    SetConsoleOutputCP(CP_UTF8);

    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

using namespace std;

void runAndPrint(const string& name, SearchAlgorithm& algorithm,
                  const vector<vector<int>>& map, const State& start, const State& goal) {
    cout << "\n=== " << name << " ===\n";

    const auto solution = algorithm.search();

    if (solution == nullptr) {
        cout << "Nenhum caminho encontrado.\n";
        return;
    }

    cout << "Custo total: " << solution->g << "\n";
    cout << "Nos visitados: " << algorithm.getVisitedNodes() << "\n";
    cout << "Nos gerados: " << algorithm.getGeneratedNodes() << "\n";

    const vector<State> path = buildPath(solution);
    Map::printMap(map, start, goal, path, algorithm.getExplored());
}

int main() {
#ifdef _WIN32
    enableAnsiColors();
#endif
    const State start(0, 0);
    const State goal(14, 14);
    vector<vector<int>> map = Map::generateValidMap(0.30, start, goal);

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

    HillClimbing hcDeterministic(problem, &heuristic, strategyDeterministic);
    HillClimbing hcSteepest(problem, &heuristic, strategySteepest);
    HillClimbing hcStochastic(problem, &heuristic, strategyStochastic);

    runAndPrint("A*", aStar, map, start, goal);
    runAndPrint("Greedy Best-First", greedy, map, start, goal);
    runAndPrint("A* (h x3)", aStarH3, map, start, goal);
    runAndPrint("Hill Climbing Deterministico", hcDeterministic, map, start, goal);
    runAndPrint("Hill Climbing Steepest", hcSteepest, map, start, goal);
    runAndPrint("Hill Climbing Estocastico", hcStochastic, map, start, goal);

    return 0;
}