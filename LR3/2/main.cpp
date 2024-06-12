#include <iostream>

#include "cubic_spline.hpp"

using namespace std;

const vector<pair<double, double>> nodes = {
    {0.0, 0.0},
    {1.7, 3.0038},
    {3.4, 5.2439},
    {5.1, 7.3583},
    {6.8, 9.4077}
};

const double x = 3.0;

// Выписать условия в точках стыковки

int main() {

    CubicSpline spline(nodes);

    double res = spline.solve(x);
    cout << "Значение функции: " << res << endl;

    for (const auto& [x, y] : nodes) {
        cout << "Значение функции и вычисленное значение: " << y << '\t' << spline.solve(x) << endl;
    }

    double eps = 0.001;
    for (int i = 1; i < nodes.size() - 1; ++i) {
        cout << spline.solve(nodes[i].first - eps) << ' ' << spline.solve(nodes[i].first + eps) << endl;
    }

    return 0;

}