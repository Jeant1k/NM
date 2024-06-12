#pragma once

#include "solver.hpp"

class Iteration : public Solver {
public:
    Iteration(Equation& eq, Equation& phi, double eps) : Solver(eq, phi, eps), numIters(0) {}
    void solve(const vector<double>& params) override;
    void printRoots() override;
    void printNumIters() override { cout << numIters; }

private:
    vector<double> roots;
    int numIters;
};