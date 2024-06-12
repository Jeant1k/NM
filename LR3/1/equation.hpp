#pragma once

#include <cmath>
#include <functional>

using namespace std;

class Equation {
public:
    Equation(function<double(const vector<double>&)> func) : func(func) {}
    double eval(const vector<double>& args) const { return func(args); }

private:
    function<double(const vector<double>&)> func;
};