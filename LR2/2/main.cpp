#include <iostream>
#include <cmath>
#include <memory>
#include <iomanip>

#define DIMS 2  // Размерность пространства

#include "eq_system.hpp"
#include "solver.hpp"
#include "newton.hpp"
#include "simple_iteration.hpp"

using namespace std;


EqSystem<double, double> sys({
    Equation<double, double>([](const double& x1, const double& x2) {
        return 4 * x1 - cos(x2);
    }),
    Equation<double, double>([](const double& x1, const double x2) {
        return 4 * x2 - exp(x1);
    })
},
{
    {
        Equation<double, double>([](const double& x1, const double& x2) {
            return 4;
        }),
        Equation<double, double>([](const double& x1, const double& x2) {
            return sin(x2);
        })
    },
    {
        Equation<double, double>([](const double& x1, const double& x2) {
            return -exp(x1);
        }),
        Equation<double, double>([](const double& x1, const double& x2) {
            return 4;
        })
    }
});

EqSystem<double, double> sysPhi({
    Equation<double, double>([](const double& x1, const double& x2) {
        return 4 * x1 - cos(x2);
    }),
    Equation<double, double>([](const double& x1, const double x2) {
        return 4 * x2 - exp(x1);
    })
},
{
    Equation<double, double>([](const double& x1, const double& x2) {
        return cos(x2) / 4.0;
    }),
    Equation<double, double>([](const double& x1, const double& x2) {
        return exp(x1) / 4.0;
    })
});


const double eps = 0.0001;
const vector<double> initRoots = {1, 1};
const double q = 0.412;


int main() {

    cout << fixed << setprecision(15);

    shared_ptr<Solver<double, double>> nt(new Newton<double, double>(sys, eps));
    nt->solve(initRoots);
    cout << "Корни уравнения методом Ньютона:" << endl;
    nt->printRoots();
    cout << endl << endl;

    cout << "Зависимость погрешности от количества итераций:" << endl;
    double epsilon = 10;
    for (int iter = 0; iter < 9; ++iter) {
        cout << epsilon << '\t';
        shared_ptr<Solver<double, double>> nt(new Newton<double, double>(sys, epsilon));
        nt->solve(initRoots);
        nt->printRoots();
        cout << '\t';
        nt->printNumIters();
        cout << endl;
        epsilon /= 100;
    }
    cout << endl;

    shared_ptr<Solver<double, double>> it(new SimpleIteration<double, double>(sysPhi, eps));
    vector<double> params(initRoots);
    params.push_back(q);
    it->solve(params);
    cout << "Корни уравнения методом Итераций:" << endl;
    it->printRoots();
    cout << endl << endl;

    cout << "Зависимость погрешности от количества итераций:" << endl;
    epsilon = 10;
    for (int iter = 0; iter < 9; ++iter) {
        cout << epsilon << '\t';
        shared_ptr<Solver<double, double>> it(new SimpleIteration<double, double>(sysPhi, epsilon));
        vector<double> params(initRoots);
        params.push_back(q);
        it->solve(params);
        it->printRoots();
        cout << '\t';
        it->printNumIters();
        cout << endl;
        epsilon /= 100;
    }
    cout << endl;

    return 0;

}