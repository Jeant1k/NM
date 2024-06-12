#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <climits>

#include "../matrix.hpp"

class LinearSystem {
public:
    LinearSystem(Matrix& A)
        : swap_count(0)
        , L(Matrix(A[0].size()))
        , U(A)
        , rhs(std::vector<double>(A[0].size()))
    {}

    std::vector<double> solve();
    void LU_decomposition();
    double determinant();
    Matrix inverse();
    void input();

private:
    
    int swap_count;
    Matrix L;
    Matrix U;
    std::vector<double> rhs;
    
};
