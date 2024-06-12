#include <iostream>
#include <vector>
#include <iomanip>

#include "simple_iterations.hpp"
#include "seidel.hpp"

int main() {

    std::cout << "Введите размерность: ";
    int n;
    std::cin >> n;

    Matrix A(n);
    A.input();


    SimpleIterations method1(n);
    method1.input(A);

    auto result = method1.solve();

    std::cout << "Количество шагов: " << result.second << std::endl;
    std::cout << "Решение:"<< std::endl << std::fixed << std::setprecision(2);
    for (double x : result.first) std::cout << x << '\t';
    std::cout << std::endl;


    Seidel method2(n);
    method2.input(A);

    result = method2.solve();

    std::cout << "Количество шагов: " << result.second << std::endl;
    std::cout << "Решение:"<< std::endl << std::fixed << std::setprecision(2);
    for (double x : result.first) std::cout << x << '\t';
    std::cout << std::endl;


    return 0;

}