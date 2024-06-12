#pragma once

#include <vector>
#include <cmath>
#include <climits>

class LinearSystem {
public:
    LinearSystem(const std::vector<std::vector<double>>& A, const std::vector<double>& rhs)
        : swap_count(0)
        , L(rhs.size(), std::vector<double>(rhs.size(), 0.0))
        , U(A)
        , rhs(rhs)
    {}

    std::vector<double> solve() {

        int n = rhs.size();

        std::vector<double> z(n);
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < i; ++j)
                sum += L[i][j] * z[j];
            z[i] = rhs[i] - sum;
        }

        std::vector<double> x(n);
        for (int i = n - 1; i >= 0; --i) {
            double sum = 0;
            for (int j = i + 1; j < n; ++j)
                sum += U[i][j] * x[j];
            x[i] = (z[i] - sum) / U[i][i];
        }

        return x;

    }

    void LU_decomposition() {

        int n = rhs.size();

        for (int i = 0; i < n; ++i) L[i][i] = 1;

        for (int i = 0; i < n; ++i) {
            int max_i = i;
            for (int j = i + 1; j < n; ++j)
                if (abs(U[j][i]) > abs(U[j][max_i]))
                    max_i = j;
            if (i != max_i) {
                swap(U[i], U[max_i]);
                ++swap_count;
            }
            for (int j = i + 1; j < n; ++j) {
                double coeff = -U[j][i] / U[i][i];
                L[j][i] = -coeff;
                U[j][i] = 0;
                for (int k = i + 1; k < n; ++k)
                    U[j][k] += coeff * U[i][k];
            }
        }

    }

private:
    int swap_count;
    std::vector<std::vector<double>> L;
    std::vector<std::vector<double>> U;
    std::vector<double> rhs;
    
};
