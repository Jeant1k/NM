#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>

#include "../matrix.hpp"

class LinearSystem {
public:
    LinearSystem(int n)
        : matrix(n, std::vector<double>(3, 0))
        , rhs(std::vector<double>(n, 0))
        , n(n)
    {}
    std::vector<double> solve();
    void input(Matrix& A);

private:
    std::vector<std::vector<double>> matrix;
    std::vector<double> rhs;
    int n;
    
};
