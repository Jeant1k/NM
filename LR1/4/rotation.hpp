#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>

#include "../matrix.hpp"

class Rotation {
public:
    Rotation(Matrix& matrix)
        : A(matrix)
        , size(matrix[0].size())
        , eigenvectors_(Matrix(size))
        , steps_(0)
    { for (int i = 0; i < size; ++i) eigenvectors_[i][i] = 1; }

    void solve(double eps);

    int steps();
    std::vector<double> eigenvalues();
    Matrix eigenvectors();

private:
    Matrix A;
    int size;
    Matrix eigenvectors_;
    int steps_;
};
