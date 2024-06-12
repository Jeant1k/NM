#pragma once

#include <cmath>
#include <functional>

using namespace std;

class Equation {
public:
    Equation(function<double(double)> func) : func(func) {}
    double eval(double x) { return func(x); }
private:
    function<double(double)> func;
};