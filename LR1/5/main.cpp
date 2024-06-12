#include <iostream>
#include <vector>
#include <iomanip>

#include "qr.hpp"

using namespace std;

int main() {

    cout << "Введите размерность: ";
    int n;
    cin >> n;

    Matrix A(n);
    A.input();

    QR method(A);

    cout << "Введите точность: ";
    double eps = 0;
    cin >> eps;

    method.solve(eps);

    cout << "Собственные значения:" << endl << fixed << setprecision(2);
    auto eigenvalues = method.get_eigenvalues();
    for (auto& val : eigenvalues) {
        if (std::abs(val.real()) > eps) {
            cout << val.real();
            if (val.imag() > 0) cout << '+';
        }
        if (std::abs(val.imag()) > eps) cout << val.imag() << 'i';
        cout << '\t';
    }
    cout << endl;
    
    return 0;

}