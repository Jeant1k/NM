#pragma once

#include <iostream>
#include <vector>
#include "eq_system.hpp"

using namespace std;

template<typename... Args>
class Newton;
class Itreation;

template<typename... Args>
class Solver {
public:
    Solver(EqSystem<Args...>& sys, double eps) : sys(sys), eps(eps) {}
    virtual void solve(const vector<double>& params) = 0;
    virtual void printRoots() = 0;
    virtual void printNumIters() = 0;

protected:
    EqSystem<Args...> sys;
    double eps;
};