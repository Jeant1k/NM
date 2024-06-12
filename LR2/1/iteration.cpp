#include "iteration.hpp"

void Iteration::solve(const vector<double>& params) {

    double x = 0, x0 = (params[0] + params[1]) / 2;
    double q = params[2];
    double accuracy = 0;
    do {
        x = sub.eval(x0);
        accuracy = q / (1 - q) * abs(x - x0);
        x0 = x;
        ++numIters;
    } while (accuracy > eps);

    roots.push_back(x);

}

void Iteration::printRoots() {
    for (double root : roots) {
        cout << root;
    }
}