#include "rotation.hpp"

void Rotation::solve(double eps) {

    double accuracy = 0;
    do {
        Matrix A_tmp = A;

        int m = 0, n = 0;
        double max_el = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i != j && std::abs(A_tmp[i][j]) > max_el) {
                    max_el = std::abs(A_tmp[i][j]);
                    m = i;
                    n = j;
                }
            }
        }

        Matrix U(size);
        for (int i = 0; i < size; ++i) U[i][i] = 1;
        double phi = std::atan(2 * A_tmp[m][n] / (A_tmp[m][m] - A_tmp[n][n])) / 2;
        double cos_phi = std::cos(phi), sin_phi = std::sin(phi);
        U[m][n] = -sin_phi;
        U[n][m] = sin_phi;
        U[m][m] = U[n][n] = cos_phi;

        A = U.transpose() * A_tmp * U;

        accuracy = 0;
        for (int i = 0; i < size - 1; ++i)
            for (int j = i + 1; j < size; ++j)
                accuracy += std::pow(A[i][j], 2);
        accuracy = std::sqrt(accuracy);

        eigenvectors_ = eigenvectors_ * U;
        ++steps_;

    } while (accuracy > eps);

}


int Rotation::steps() { return steps_; }

std::vector<double> Rotation::eigenvalues() {

    std::vector<double> eigenvalues(size);
    for (int i = 0; i < size; ++i) eigenvalues[i] = A[i][i];

    return eigenvalues;

}

Matrix Rotation::eigenvectors() { return eigenvectors_; }