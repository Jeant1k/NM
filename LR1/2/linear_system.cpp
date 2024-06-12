#include "linear_system.hpp"

void LinearSystem::input(Matrix& A) {

    for (int i = 0; i < n; ++i) {
        if (i - 1 >= 0) matrix[i][0] = A[i][i - 1];
        matrix[i][1] = A[i][i];
        if (i + 1 < n) matrix[i][2] = A[i][i + 1];
    }

    std::cout << "Введите правую часть:" << std::endl;
    for (int i = 0; i < n; ++i) std::cin >> rhs[i];

}

std::vector<double> LinearSystem::solve() {

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
