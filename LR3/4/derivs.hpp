#pragma once

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Deriv {
public:
    Deriv(const vector<pair<double, double>>& funcTable) : table(funcTable) {}

    double firstDeriv(const double x) {

        int idx = -1;
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].first == x) {
                idx = i;
                break;
            }
        }

        if (idx == -1) throw runtime_error("Indefinite value " + to_string(x));

        double left = (table[idx].second - table[idx - 1].second) / (table[idx].first - table[idx - 1].first);
        double right = (table[idx + 1].second - table[idx].second) / (table[idx + 1].first - table[idx].first);

        return left + (right - left) * (2 * x - table[idx - 1].first - table[idx].first) /
                                       (table[idx + 1].first - table[idx - 1].first);

    }

    double secondDeriv(const double x) {
        
        int idx = -1;
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].first == x) {
                idx = i;
                break;
            }
        }

        if (idx == -1) throw runtime_error("Indefinite value " + to_string(x));

        double left = (table[idx].second - table[idx - 1].second) / (table[idx].first - table[idx - 1].first);
        double right = (table[idx + 1].second - table[idx].second) / (table[idx + 1].first - table[idx].first);

        return 2 * (right - left) / (table[idx + 1].first - table[idx - 1].first);

    }

private:
    vector<pair<double, double>> table;

};
