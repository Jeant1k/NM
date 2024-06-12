#include <iostream>
#include <vector>
#include <iomanip>

#include "rotation.hpp"

int main() {

    std::cout << "Введите размерность: ";
    int n;
    std::cin >> n;

    Matrix A(n);
    A.input();

    Rotation method(A);

    std::cout << "Введите точность: ";
    double eps = 0;
    std::cin >> eps;

    method.solve(eps);

    std::cout << "Количество шагов:" << std::endl << method.steps() << std::endl;

    std::cout << "Собственные значения:" << std::endl << std::fixed << std::setprecision(2);
    std::vector<double> eigenvalues = method.eigenvalues();
    for (double lambda : eigenvalues) std::cout << lambda << '\t';
    std::cout << std::endl;

    std::cout << "Собственные векторы:" << std::endl;
    Matrix eigenvectors = method.eigenvectors();
    eigenvectors.print();

    std::cout << "Зависимость погрешности от точности:" << std::fixed << std::setprecision(15) << std::endl;
    eps = 10;
    for (int iter = 0; iter < 10; ++iter) {
        std::cout << eps << '\t';
        Rotation method(A);
        method.solve(eps);
        std::cout << method.steps() << '\t';
        Matrix eigenvectors = method.eigenvectors();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double sum = 0;
                for (int k = 0; k < n; ++k)
                    sum += eigenvectors[k][i] * eigenvectors[k][j];
                std::cout << sum << '\t';
            }
        }
        std::cout << std::endl;
        eps /= 10;
    }
    std::cout << std::endl;

    // A * x = lambda * x

    return 0;

}