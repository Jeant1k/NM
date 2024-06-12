#include "newton.hpp"

void Newton::solve(const vector<double>& params) {

    double x = 0, x0 = params[0];
    double accuracy = 0;
    do {
        x = x0 - eq.eval(x0) / sub.eval(x0);
        accuracy = abs(x - x0);
        x0 = x;
        ++numIters;
    } while (accuracy > eps);

    roots.push_back(x);

}

void Newton::printRoots() {
    for (double root : roots) {
        cout << root;
    }
}