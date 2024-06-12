#include "matrix.hpp"

Matrix Matrix::operator+(const Matrix& other) const {

    if (data.size() != other.data.size() || data[0].size() != other.data[0].size())
        throw std::invalid_argument("Matrices dimensions do not match");

    Matrix result(data.size(), data[0].size());
    for (int i = 0; i < data.size(); ++i)
        for (int j = 0; j < data[0].size(); ++j)
            result.data[i][j] = data[i][j] + other.data[i][j];

    return result;

}

Matrix Matrix::operator*(const Matrix& other) const {

    if (data[0].size() != other.data.size())
        throw std::invalid_argument("Matrices dimensions do not match");

    Matrix result(data.size(), other.data[0].size());
    for (int i = 0; i < result.data.size(); ++i)
        for (int j = 0; j < result.data[0].size(); ++j)
            for (int k = 0; k < data[0].size(); ++k)
                result.data[i][j] += data[i][k] * other.data[k][j];

    return result;

}

Matrix Matrix::transpose() const {

    Matrix result(data[0].size(), data.size());
    for (int i = 0; i < data.size(); ++i)
        for (int j = 0; j < data[0].size(); ++j)
            result.data[j][i] = data[i][j];

    return result;

}

void Matrix::input() {

    std::cout << "Введите матрицу:" << std::endl; 
    for (int i = 0; i < data.size(); i++)
        for (int j = 0; j < data[i].size(); j++)
            std::cin >> data[i][j];

}

void Matrix::print() const {

    std::cout << std::fixed << std::setprecision(2) << "Матрица:" << std::endl;
    for (const auto& row : data) {
        for (const auto& elem : row)
            std::cout << elem << '\t';
        std::cout << std::endl;
    }
    std::cout << std::defaultfloat;

}

std::vector<double>& Matrix::operator[](int i) {

    if (i < 0 || i >= data.size()) {
        throw std::out_of_range("Index is out of range");
    }

    return data[i];

}

void Matrix::swap_rows(int row1, int row2) {

    if (row1 < 0 || row1 >= data.size() || row2 < 0 || row2 >= data.size()) {
        throw std::out_of_range("Index is out of range");
    }

    std::swap(data[row1], data[row2]);
    
}
