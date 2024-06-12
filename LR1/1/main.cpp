#include <iostream>
#include <vector>
#include <iomanip>

#include "linear_system.hpp"

int main() {

    std::cout << "Введите размерность: ";
    int n;
    std::cin >> n;

    Matrix A(n);
    A.input();

    LinearSystem system(A);
    system.input();
    system.LU_decomposition();

    std::vector<double> result = system.solve();
    std::cout << "Решение:"<< std::endl << std::fixed << std::setprecision(2);
    for (int i = 0; i < n; ++i)
        std::cout << result[i] << '\t';
    std::cout << std::endl;

    std::cout << "Определитель: " << system.determinant() << std::endl;

    Matrix I = system.inverse();
    I.print();

    (A * I).print();    // Проверка

    return 0;

}