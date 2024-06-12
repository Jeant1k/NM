#pragma once

#include <cmath>
#include <iostream>

#include "equation.hpp"

using namespace std;

class SimpsonMethod {
public:
    double integr(const Equation& fun, const double X0, const double Xk, const double h) {
        
        double res = fun.eval({X0});
        double factor = 4.0;
        for (double x = X0 + h; x < Xk; x += h) {
            res += factor * fun.eval({x});
            factor = factor == 4.0 ? 2.0 : 4.0;
        }

        return (res + fun.eval({Xk})) * h / 3;
    }
};