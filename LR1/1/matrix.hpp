#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

class Matrix {
private:
    std::vector<std::vector<double>> data;

public:
    Matrix(int n, int m) : data(n, std::vector<double>(m, 0)) {}
    Matrix(int n) : data(n, std::vector<double>(n, 0)) {}

    std::vector<double>& operator[](int i);
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix transpose() const;
    void input();
    void print() const;
    void swap_rows(int row1, int row2);
    
};
