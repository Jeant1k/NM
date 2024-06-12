#include "simple_iterations.hpp"

void SimpleIterations::input(Matrix& A) {

    std::cout << "Введите правую часть:" << std::endl;
    for (int i = 0; i < n; ++i) std::cin >> rhs[i];

    std::cout << "Введите точность: ";
    std::cin >> eps;

    for (int i = 0; i < n; ++i) {
        if (A[i][i] == 0) {
            bool flag = false;
            for (int j = i + 1; j < n; ++j) {
                if (A[j][i] != 0) {
                    A.swap_rows(i, j);
                    flag = true;
                    break;
                }
            }
            if (!flag) throw std::invalid_argument("Column consists of zeros");
        }
        beta[i] = rhs[i] / A[i][i];
        for (int j = 0; j < n; ++j)
            if (i != j) alpha[i][j] = -A[i][j] / A[i][i];
    }

}

// TODO: вычисление критерия окончания по другой формуле

std::pair<std::vector<double>, int> SimpleIterations::solve() {

    std::vector<double> X = beta;
    int k = 0;
    double norm_a = alpha.norm(), accuracy = 0;
    do {
        std::vector<double> tmp = alpha * X;
        for (int i = 0; i < n; ++i) tmp[i] += beta[i];

        accuracy = norm_a / (1 - norm_a);
        double norm_x = 0;
        for (int i = 0; i < n; ++i)
            norm_x = std::max(norm_x, std::abs(tmp[i] - X[i]));
        accuracy *= norm_x;

        X = tmp;
        ++k;

    } while (accuracy > eps);

    return make_pair(X, k);

}
