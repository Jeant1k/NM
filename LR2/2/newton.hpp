#pragma once

#include "solver.hpp"

template<typename... Args>
class Newton : public Solver<Args...> {
public:
    Newton(EqSystem<Args...>& sys, double eps) : Solver<Args...>(sys, eps), numIters(0) {}

    void printNumIters() { cout << numIters; }

    void solve(const vector<double>& initRoots) {

        int dim = initRoots.size();

        vector<double> x(dim, 0), x0 = initRoots;
        double accuracy = 0;
        do {
            // cout << "Итерация #" << numIters << ":" << endl;

            vector<vector<double>> J = apply([this](auto&&... args) { return this->sys.evalJ(args...); }, vec2Tuple<DIMS>(x0));

            // cout << "\tМатрица Якоби:" << endl;
            // for (auto& row : J) {
            //     for (auto& el : row)
            //         cout << '\t' << el << ' ';
            //     cout << endl;
            // }

            vector<double> eval = apply([this](auto&&... args) { return this->sys.evalSystem(args...); }, vec2Tuple<DIMS>(x0));
            for (int i = 0; i < dim; ++i) {
                vector<vector<double>> A = J;
                for (int j = 0; j < dim; ++j)
                    A[j][i] = eval[j];
                // cout << "\tМатрица A:" << endl;
                // for (auto& row : A) {
                //     for (auto& el : row) cout << '\t' << el << ' ';
                //     cout << endl;
                // }
                x[i] = x0[i] - determinant(A) / determinant(J);
            }

            // cout << "\tВектор x: ";
            // for (double el : x) cout << el << ' ';
            // cout << endl;

            accuracy = 0;
            for (int i = 0; i < dim; ++i)
                accuracy = max(abs(x[i] - x0[i]), accuracy);

            // cout << "\tТочность: " << accuracy << endl;
            
            x0 = x;
            ++numIters;

        } while (accuracy > this->eps);

        roots.push_back(x);

    }

    void printRoots() {

        for (auto& root : roots) {
            cout << "(";
            for (int j = 0; j < root.size(); ++j) {
                cout << root[j];
                if (j < root.size() - 1) cout << ' ';
            }
            cout << ") ";
        }

    }

private:
    double determinant(const vector<vector<double>>& matrix) {

        int size = matrix.size();

        if (size == 1) {
            return matrix[0][0];
        } else if (size == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else {
            double det = 0;
            for (int i = 0; i < size; ++i) {
                vector<vector<double>> submatrix;
                for (int j = 1; j < size; ++j) {
                    vector<double> row;
                    for (int k = 0; k < size; ++k) {
                        if (k != i) {
                            row.push_back(matrix[j][k]);
                        }
                    }
                    submatrix.push_back(row);
                }
                det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(submatrix);
            }
            return det;
        }

    }

    vector<vector<double>> roots;
    int numIters;
    
};