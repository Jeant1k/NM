#include <iostream>
#include <vector>
#include <iomanip>

#include "equation.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "simpson.hpp"

using namespace std;

const Equation fun1([](const vector<double>& args) {
    return args[0] / (16 - pow(args[0], 4));
});

const Equation fun([](const vector<double>& args) {
    return args[0] / pow(3 * args[0] + 4, 2);
});

const double X0 = -1, Xk = 1;
const double h1 = 0.5, h2 = 0.25;

double rungeRombergRichardson(double Ih, double I2h, int p) {
    return Ih + (Ih - I2h) / (pow(2, p) - 1);
}

int main() {

    RectangleMethod rect;
    TrapezoidMethod trap;
    SimpsonMethod simp;

    double rect_h1 = rect.integr(fun1, X0, Xk, h1);
    double rect_h2 = rect.integr(fun1, X0, Xk, h2);
    double rect_RRR = rungeRombergRichardson(rect_h2, rect_h1, 2);

    double trap_h1 = trap.integr(fun1, X0, Xk, h1);
    double trap_h2 = trap.integr(fun1, X0, Xk, h2);
    double trap_RRR = rungeRombergRichardson(trap_h2, trap_h1, 2);

    double simp_h1 = simp.integr(fun1, X0, Xk, h1);
    double simp_h2 = simp.integr(fun1, X0, Xk, h2);
    double simp_RRR = rungeRombergRichardson(simp_h2, simp_h1, 2);

    cout << fixed << setprecision(10);

    cout << "Rectangle Method h1: " << rect_h1 << endl;
    cout << "Trapezoid Method h1: " << trap_h1 << endl;
    cout << "Simpson Method h1: " << simp_h1 << endl;

    cout << "Rectangle Method h2: " << rect_h2 << endl;
    cout << "Trapezoid Method h2: " << trap_h2 << endl;
    cout << "Simpson Method h2: " << simp_h2 << endl;

    cout << "Rectangle Method: " << rect_RRR << endl;
    cout << "Trapezoid Method: " << trap_RRR << endl;
    cout << "Simpson Method: " << simp_RRR << endl;

    return 0;
}
