#include <iostream>
#include <cmath>
#include <memory>
#include <iomanip>

#include "equation.hpp"
#include "solver.hpp"
#include "newton.hpp"
#include "iteration.hpp"

using namespace std;

int main() {

    cout << fixed << setprecision(15);

    Equation eq([](const double& x) {
        return log(x + 1) - pow(x, 3) + 1;
    });

    Equation der([](const double& x) {
        return 1 / (x + 1) - 3 * pow(x, 2);
    });

    double eps;
    cout << "Введите eps: ";
    cin >> eps;

    double x0;
    cout << "Введите x0: ";
    cin >> x0;

    shared_ptr<Solver> nt(new Newton(eq, der, eps));
    nt->solve({x0});
    cout << "Корни уравнения методом Ньютона:" << endl;
    nt->printRoots();
    cout << endl;

    cout << "Зависимость погрешности от количества итераций:" << endl;
    eps = 10;
    for (int iter = 0; iter < 9; ++iter) {
        cout << eps << '\t';
        shared_ptr<Solver> nt(new Newton(eq, der, eps));
        nt->solve({x0});
        nt->printRoots();
        cout << '\t';
        nt->printNumIters();
        cout << endl;
        eps /= 100;
    }

    Equation phi([](const double& x) {
        return pow(log(x + 1) + 1, 1.0 / 3.0);
    });

    Equation der_phi([](const double& x) {
        return 1 / (3 * (x + 1) * pow(pow(log(x + 1) + 1, 2), 1.0 / 3.0));
    });

    double a, b, q;
    cout << "Введите a и b: ";
    cin >> a >> b;
    double x = a;
    for (int i = 0; i < 100; ++i) {
        q = max(q, abs(der_phi.eval(x)));
        x += (b - a) / 100;
    }

    shared_ptr<Solver> it(new Iteration(eq, phi, eps));
    it->solve({a, b, q});
    cout << "Корни уравнения методом Итераций:" << endl;
    it->printRoots();
    cout << endl;

    cout << "Зависимость погрешности от количества итераций:"<< endl;
    eps = 10;
    for (int iter = 0; iter < 10; ++iter) {
        cout << eps << '\t';
        shared_ptr<Solver> it(new Iteration(eq, phi, eps));
        it->solve({a, b, q});
        it->printRoots();
        cout << '\t';
        it->printNumIters();
        cout << endl;
        eps /= 100;
    }

    return 0;

}