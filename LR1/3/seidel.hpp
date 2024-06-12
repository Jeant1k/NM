#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>

#include "simple_iterations.hpp"

class Seidel : public SimpleIterations {
public:
    Seidel(int n) : SimpleIterations(n) {}

    std::pair<std::vector<double>, int> solve();
};