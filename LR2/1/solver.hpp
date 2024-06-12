#pragma once

#include <iostream>
#include <vector>
#include "equation.hpp"

using namespace std;

class Newton;
class Itreation;

class Solver {
public:
    Solver(Equation& eq, Equation& sub, double eps) : eq(eq), sub(sub), eps(eps) {}
    virtual void solve(const vector<double>& params) = 0;
    virtual void printRoots() = 0;
    virtual void printNumIters() = 0;

protected:
    Equation eq;
    Equation sub;
    double eps;
};