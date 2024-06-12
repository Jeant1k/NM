#pragma once

#include <cmath>
#include <iostream>

#include "equation.hpp"

using namespace std;

class TrapezoidMethod {
public:
    double integr(const Equation& fun, const double X0, const double Xk, const double h) {
        
        double res = fun.eval({X0}) / 2;
        for (double x = X0 + h; x < Xk; x += h) {
            res += fun.eval({x});
        }

        return (res + fun.eval({Xk}) / 2) * h;

    }
};