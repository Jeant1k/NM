#pragma once

#include <vector>
#include <cmath>
#include <climits>
#include <iostream>
#include <unordered_map>

#include "linear_system.hpp"

using namespace std;

class LSM {
public:
    LSM(const vector<pair<double, double>>& table) : table(table), n(table.size()) {}

    vector<double> polynom(int size) {

        // Нормальная система МНК
        // В матрице на побочных диагоналях стоят суммы иксов в степени номер диагонали - 1
        // Приближающий многочлен
        // Условие минимума квадратичного отклонения
        // Метод Крамера
        
        vector<double> rhs(size, 0.0);
        vector<vector<double>> matrix(size, vector<double>(size, 0.0));
        matrix[0][0] = n;
        for (int i = 1; i < 2 * size - 1; ++i) {
            double sum = 0.0;
            double rhsSum = 0.0;
            for (int j = 0; j < n; ++j) {
                sum += pow(table[j].first, i);
                rhsSum += table[j].second * pow(table[j].first, i - 1);
            }
            for (int j = 0; j < i + 1; ++j) if (j < size && i - j < size) matrix[j][i - j] = sum;
            if (i - 1 < size) rhs[i - 1] = rhsSum;
        }

        LinearSystem sys(matrix, rhs);

        sys.LU_decomposition();
        vector<double> sol = sys.solve();

        coeffs[size] = sol;

        return sol;

    }

    double polynomEval(int size, double val) {

        if (!coeffs.contains(size))
            throw runtime_error("Polynomial of size " + to_string(size) + " not calculated");
        
        double eval = 0.0;
        int pos = 0;
        for (const double coeff : coeffs[size]) eval += coeff * pow(val, pos++);

        return eval;

    }

    double polynoomError(int size) {

        if (!coeffs.contains(size))
            throw runtime_error("Polynomial of size " + to_string(size) + " not calculated");

        double err = 0.0;
        for (int i = 0; i < n; ++i)
            err += pow(polynomEval(size, table[i].first) - table[i].second, 2);
        
        return err;
        
    }

private:
    vector<pair<double, double>> table;
    unordered_map<int, vector<double>> coeffs;
    int n;

};
