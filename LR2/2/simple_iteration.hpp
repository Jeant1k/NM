#pragma once

#include "solver.hpp"

template<typename... Args>
class SimpleIteration : public Solver<Args...> {
public:
    SimpleIteration(EqSystem<Args...>& sysPhi, double eps) : Solver<Args...>(sysPhi, eps), numIters(0) {}

    void printNumIters() { cout << numIters; }

    void solve(const vector<double>& initRoots) {

        vector<double> x0(initRoots.begin(), initRoots.end() - 1), x;
        double q = initRoots.back();
        double accuracy = 0;
        do {
            x = apply([this](auto&&... args) { return this->sys.evalPhi(args...); }, vec2Tuple<DIMS>(x0));
            
            double norm = 0.0;
            for (int i = 0; i < initRoots.size(); ++i) norm = max(norm, abs(x[i] - x0[i]));
            accuracy = q / (1 - q) * norm;

            x0 = x;
            ++numIters;
        } while (accuracy > this->eps);

        roots.push_back(x);

    }

    void printRoots() {

        for (auto& root : roots) {
            cout << "(";
            for (int j = 0; j < root.size(); ++j) {
                cout << root[j];
                if (j < root.size() - 1) cout << ' ';
            }
            cout << ") ";
        }

    }

private:
    vector<vector<double>> roots;
    int numIters;
    
};