#pragma once

#include "equation.hpp"

using namespace std;

class Lagrange {
public:
    Lagrange(const Equation& fun, const vector<double>& X_i)
        : fun(fun)
        , X_i(X_i)
        , dim(X_i.size())
    {}

    double solve(const double X) {
        double res = 0.0;
        for (int i = 0; i < dim; ++i) {
            double polynoms = 1.0;
            double prod = 1.0;
            for (int j = 0; j < dim; ++j) {
                if (i == j) continue;
                polynoms *= (X - X_i[j]) / (X_i[i] - X_i[j]);
                prod *= (X_i[i] - X_i[j]);
            }
            double coeff = fun.eval({X_i[i]}) / prod;
            if (abs(coeff) > 0.0001) {
                if (coeff > 0) cout << '+';
                cout << coeff;
                for (int j = 0; j < dim; ++j) {
                    if (i == j) continue;
                    cout << "(x";
                    if (-X_i[j] > 0) cout << '+';
                    cout << -X_i[j] << ")";
                }
                cout << ' ';
            }
            res += fun.eval({X_i[i]}) * polynoms;
        }
        cout << endl;
        return res;
    }

private:
    Equation fun;
    vector<double> X_i;
    int dim;

};