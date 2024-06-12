#pragma once

#include "equation.hpp"

using namespace std;

class Newton {
public:
    Newton(const Equation& fun, const vector<double>& X_i)
        : fun(fun)
        , X_i(X_i)
        , dim(X_i.size())
    {}

    double solve(const double X) {

        vector<vector<double>> finDifTable(dim);
        for (int i = 0; i < dim; ++i) finDifTable[0].push_back(fun.eval({X_i[i]}));

        for (int i = 1; i < dim; ++i)
            for (int j = 0; j < dim - i; ++j)
                finDifTable[i].push_back((finDifTable[i - 1][j] - finDifTable[i - 1][j + 1]) / (X_i[j] - X_i[i + j]));
       
        double res = 0.0;
        for (int i = 0; i < dim; ++i) {
            double term = finDifTable[i][0];
            if (abs(term) > 0.001) {
                if (term > 0) cout << '+';
                cout << term;
                for (int j = 0; j < i; ++j) {
                    cout << "(x";
                    if (-X_i[j] > 0) cout << '+';
                    cout << -X_i[j] << ")";
                }
                cout << ' ';
            }
            for (int j = 0; j < i; ++j) term *= (X - X_i[j]);
            res += term;
        }
        cout << endl;

        return res;

    }

private:
    Equation fun;
    vector<double> X_i;
    int dim;

};