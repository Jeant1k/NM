#pragma once

#include <cmath>
#include <iostream>

#include "equation.hpp"

using namespace std;

class RectangleMethod {
public:
    double integr(const Equation& fun, const double X0, const double Xk, const double h) {
        
        double res = 0.0;
        for (double x = X0 + h; x <= Xk; x += h) {
            res += fun.eval({(x + x - h) / 2});
        }

        return res * h;

    }
};