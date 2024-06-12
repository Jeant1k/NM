#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>

#include "../matrix.hpp"

class SimpleIterations {
public:
    SimpleIterations(int n)
        : alpha(Matrix(n))
        , beta(std::vector<double>(n, 0))
        , rhs(std::vector<double>(n, 0))
        , eps(0)
        , n(n)
    {}
    std::pair<std::vector<double>, int> solve();
    void input(Matrix& A);

protected:
    Matrix alpha;
    std::vector<double> beta;
    std::vector<double> rhs;
    double eps;
    int n;
};
