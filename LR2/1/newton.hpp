#pragma once

#include "solver.hpp"

class Newton : public Solver {
public:
    Newton(Equation& eq, Equation& der, double eps) : Solver(eq, der, eps), numIters(0) {}
    void solve(const vector<double>& params) override;
    void printRoots() override;
    void printNumIters() override { cout << numIters; }

private:
    vector<double> roots;
    int numIters;
};