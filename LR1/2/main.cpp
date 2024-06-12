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

    LinearSystem system(n);
    system.input(A);

    std::vector<double> solution = system.solve();
    
    std::cout << "Решение:"<< std::endl << std::fixed << std::setprecision(2);
    for (double x : solution) std::cout << x << '\t';
    std::cout << std::endl;

    return 0;

}