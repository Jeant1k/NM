#include <iostream>
#include <vector>

#include "lsm.hpp"

using namespace std;

const vector<pair<double, double>> funcTable = {
    {0.0, 0.0},
    {1.7, 3.0038},
    {3.4, 5.2439},
    {5.1, 7.3583},
    {6.8, 9.4077},
    {8.5, 11.415}
};

int main() {

    LSM method(funcTable);

    vector<double> coeffs1 = method.polynom(2);
    vector<double> coeffs2 = method.polynom(3);

    cout << "Ошибка для многочлена 2 степени: " << method.polynoomError(2) << endl;
    cout << "Ошибка для многочлена 2 степени: " << method.polynoomError(3) << endl;

    vector<pair<double, double>> points1;
    vector<pair<double, double>> points2;

    double a = 0, b = 9;
    double step = (b - a) / 19;
    for (int i = 0; i < 20; ++i) {
        points1.push_back(make_pair(a, method.polynomEval(2, a)));
        a += step;
    }

    a = 0;
    for (int i = 0; i < 20; ++i) {
        points2.push_back(make_pair(a, method.polynomEval(3, a)));
        a += step;
    }

    cout << funcTable.size() << endl;
    for (const auto& [x, y] : funcTable) cout << x << ' ' << y << endl;
    cout << points1.size() << endl;
    for (const auto& [x, y] : points1) cout << x << ' ' << y << endl;
    cout << points2.size() << endl;
    for (const auto& [x, y] : points2) cout << x << ' ' << y << endl;

    return 0;

}