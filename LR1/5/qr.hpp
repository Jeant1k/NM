#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>
#include <complex>

#include "../matrix.hpp"

class QR {
public:
    QR(Matrix& matrix)
        : A(matrix)
        , Q(Matrix(matrix.size()))
        , R(Matrix(matrix.size()))
        , n(matrix.size())
        , eigenvalues(std::vector<std::complex<double>>(matrix.size(), 0))
    {}

    void solve(double eps);
    std::vector<std::complex<double>> get_eigenvalues();

private:
    int sign(double num) const;
    std::pair<std::complex<double>, std::complex<double>>
        solve(double ajj, double aj1j1, double ajj1, double aj1j);

    Matrix A, Q, R;
    std::vector<std::complex<double>> eigenvalues;
    int n;
};
