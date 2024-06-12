#include <iostream>
#include <vector>

#include "derivs.hpp"

using namespace std;

const vector<pair<double, double>> funcTable = {
    {-0.2, 1.5722},
    {0.0, 1.5708},
    {0.2, 1.5694},
    {0.4, 1.5593},
    {0.6, 1.5273}
};

const double X = 0.2;

int main() {

    Deriv der(funcTable);

    cout << "Первая производная = " << der.firstDeriv(X) << endl;
    cout << "Вторая производная = " << der.secondDeriv(X) << endl;

    return 0;

}