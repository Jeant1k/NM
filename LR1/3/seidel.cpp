#include "seidel.hpp"

std::pair<std::vector<double>, int> Seidel::solve() {

    Matrix C(n);
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            C[i][j] = alpha[i][j];

    std::vector<double> X = beta;
    int k = 0;
    double norm_a = alpha.norm(), norm_c = C.norm(), accuracy = 0;
    do {
        std::vector<double> tmp(n, 0);
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < i; ++j)
                sum += alpha[i][j] * tmp[j];
            for (int j = i; j < n; ++j)
                sum += alpha[i][j] * X[j];
            tmp[i] += beta[i] + sum;
        }

        accuracy = norm_c / (1 - norm_a);
        double norm_x = 0;
        for (int i = 0; i < n; ++i)
            norm_x = std::max(norm_x, std::abs(tmp[i] - X[i]));
        accuracy *= norm_x;

        X = tmp;
        ++k;

    } while (accuracy > eps);

    return make_pair(X, k);

}
