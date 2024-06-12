#include <iostream>
#include <memory>

#include "equation.hpp"
#include "lagrange.hpp"
#include "newton.hpp"

using namespace std;

const Equation fun([](const vector<double>& args) {
    return sqrt(args[0]) + args[0];
});

const vector<double> X_i_1 = {0, 1.7, 3.4, 5.1};
const vector<double> X_i_2 = {0, 1.7, 4.0, 5.1};
const double X = 3.0;

// Выписать палином

int main() {

    shared_ptr<Lagrange> L(new Lagrange(fun, X_i_1));
    double val = L->solve(X);
    cout << "Значение многочлена: " << val << endl;
    cout << "Значение функции: " << fun.eval({X}) << endl;
    cout << "Погрешность: " << abs(val - fun.eval({X})) << endl;

    shared_ptr<Newton> N(new Newton(fun, X_i_2));
    val = N->solve(X);
    cout << "Значение многочлена: " << val << endl;
    cout << "Значение функции: " << fun.eval({X}) << endl;
    cout << "Погрешность: " << abs(val - fun.eval({X})) << endl;

    return 0;

}