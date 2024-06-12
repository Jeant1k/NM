#pragma once

#include <cmath>

#include "linear_system.hpp"

using namespace std;

class CubicSpline {
public:
    CubicSpline(const vector<pair<double, double>>& nodes)
        : nodes(nodes)
        , dim(nodes.size() - 1)
        , table(nodes.size() - 1, vector<double>(4, 0))
    {

        vector<double> rhs(dim - 1, 0);
        vector<vector<double>> matrix(dim - 1, vector<double>(3, 0));
        for (int i = 0; i < dim - 1; ++i) {
            if (i > 0) matrix[i][0] = h(i + 1);
            matrix[i][1] = 2 * (h(i + 1) + h(i + 2));
            if (i < dim - 2) matrix[i][2] = h(i + 2);

            rhs[i] = 3 * ((f(i + 2) - f(i + 1)) / h(i + 2) - (f(i + 1) - f(i)) / h(i + 1));
        }

        LinearSystem sys(matrix, rhs);
        vector<double> sol = sys.solve();

        for (int i = 0; i < dim; ++i) {
            table[i][0] = f(i);
            if (i > 0) table[i][2] = sol[i - 1];
        }
        for (int i = 0; i < dim - 1; ++i) {
            table[i][1] = (f(i + 1) - f(i)) / h(i + 1) - h(i + 1) * (table[i + 1][2] + 2 * table[i][2]) / 3;
            table[i][3] = (table[i + 1][2] - table[i][2]) / (3 * h(i + 1));
        }
        table[dim - 1][1] = (f(dim) - f(dim - 1)) / h(dim) - h(dim) * 2 * table[dim - 1][2] / 3;
        table[dim - 1][3] = -table[dim - 1][2] / (3 * h(dim));

    }

    double solve(const double x) {

        int idx = -1;
        for (int i = 0; i < dim + 1; ++i) if (nodes[i].first <= x && x <= nodes[i + 1].first) idx = i;
        
        return table[idx][0] + table[idx][1] * (x - nodes[idx].first) + 
               table[idx][2] * pow((x - nodes[idx].first), 2) + table[idx][3] * pow((x - nodes[idx].first), 3);

    }

private:
    double f(int idx) { return nodes[idx].second; }
    double h(int idx) { return nodes[idx].first - nodes[idx - 1].first; }

    vector<pair<double, double>> nodes;
    vector<vector<double>> table;
    int dim;

};