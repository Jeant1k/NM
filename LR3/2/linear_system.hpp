#pragma once

#include <vector>
#include <cmath>

class LinearSystem {
public:
    LinearSystem(const std::vector<std::vector<double>>& matrix, const std::vector<double>& rhs)
        : matrix(matrix)
        , rhs(rhs)
        , n(rhs.size())
    {}

    std::vector<double> solve() {

        // Прямая прогонка
        std::vector<double> P(n), Q(n);
        P[0] = -matrix[0][2] / matrix[0][1];
        Q[0] = rhs[0] / matrix[0][1];

        for (int i = 1; i < n; ++i) {
            P[i] = -matrix[i][2] / (matrix[i][1] + matrix[i][0] * P[i - 1]);
            Q[i] = (rhs[i] - matrix[i][0] * Q[i - 1]) / (matrix[i][1] + matrix[i][0] * P[i - 1]);
        }

        // Обратная прогонка
        std::vector<double> X(n);
        X[n - 1] = Q[n - 1];
        for (int i = n - 2; i >= 0; --i)
            X[i] = P[i] * X[i + 1] + Q[i];
        
        return X;

    }

private:
    std::vector<std::vector<double>> matrix;
    std::vector<double> rhs;
    int n;
    
};
