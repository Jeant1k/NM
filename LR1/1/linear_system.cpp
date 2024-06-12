#include "linear_system.hpp"

void LinearSystem::input() {

    std::cout << "Введите правую часть:" << std::endl;
    for (int i = 0; i < rhs.size(); ++i)
        std::cin >> rhs[i];

}

void LinearSystem::LU_decomposition() {

    int n = rhs.size();

    for (int i = 0; i < n; ++i) L[i][i] = 1;

    for (int i = 0; i < n; ++i) {
        int max_i = i;
        for (int j = i + 1; j < n; ++j)
            if (abs(U[j][i]) > abs(U[j][max_i]))
                max_i = j;
        if (i != max_i) {
            U.swap_rows(i, max_i);
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

std::vector<double> LinearSystem::solve() {

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

double LinearSystem::determinant() {

    double result = pow(-1, swap_count);
    for (int i = 0; i < rhs.size(); ++i)
        result *= U[i][i];

    return result;

}

Matrix LinearSystem::inverse() {

    int n = rhs.size();

    Matrix Z(n);
    for (int i = 0; i < n; ++i) Z[i][i] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            double sum = 0;
            for (int k = 0; k < i; ++k)
                sum += L[i][k] * Z[k][j];
            Z[i][j] = -sum;
        }
    }

    Matrix X(n);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = i + 1; k < n; ++k)
                sum += U[i][k] * X[k][j];
            X[i][j] = (Z[i][j] - sum) / U[i][i];
        }
    }

    return X;

}