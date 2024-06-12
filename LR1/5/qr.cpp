#include "qr.hpp"

void QR::solve(double eps) {

    double accuracy_1 = 0, accuracy_2 = 0;
    do {

        Q = Matrix(n);
        for (int i = 0; i < n; ++i) Q[i][i] = 1;
        R = A;

        for (int i = 0; i < n - 1; ++i) {

            Matrix A_tmp = R;

            std::vector<double> v(n, 0);
            double sum = 0;
            for (int j = i; j < n; ++j) sum += std::pow(A_tmp[j][i], 2);
            v[i] = A_tmp[i][i] + sign(A_tmp[i][i]) * std::sqrt(sum);
            for (int j = i + 1; j < n; ++j) v[j] = A_tmp[j][i];

            Matrix E(n);
            for (int j = 0; j < n; ++j) E[j][j] = 1;
            Matrix TMP(n);
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    TMP[j][k] = v[j] * v[k];
            double tmp = 0;
            for (int j = 0; j < n; ++j) tmp += v[j] * v[j];
            Matrix H = E - TMP * (2 / tmp);

            R = H * A_tmp;
            Q = Q * H;

        }

        A = R * Q;

        accuracy_1 = eps * 100;
        for (int i = 0; i < n - 1; ++i) {
            double sum = 0;
            for (int j = i + 1; j < n; ++j)
                sum += std::pow(A[j][i], 2);
            accuracy_1 = std::min(accuracy_1, sum);
        }
        accuracy_1 = std::sqrt(accuracy_1);

        double sum = 0;
        for (int i = 0; i < n - 1; ++i) {
            auto roots = solve(A[i][i], A[i + 1][i + 1], A[i][i + 1], A[i + 1][i]);
            sum += roots.first.real() * roots.first.imag() + roots.second.real() * roots.second.imag();
        }
        accuracy_2 = std::abs(accuracy_2 - sum);

    } while (accuracy_1 > eps || accuracy_2 > eps);

}


std::vector<std::complex<double>> QR::get_eigenvalues() {
   
    std::vector<std::complex<double>> eigenvalues(n, std::complex<double>(0));
    for (int i = 0; i < n - 1; ++i) {
        auto roots = solve(A[i][i], A[i + 1][i + 1], A[i][i + 1], A[i + 1][i]);
        eigenvalues[i] = roots.first;
        eigenvalues[i + 1] = roots.second;
    }

    return eigenvalues;

}

int QR::sign(double num) const {
    if (num > 0) return 1;
    else if (num < 0) return -1;
    return 0;
}

std::pair<std::complex<double>, std::complex<double>> QR::solve(double ajj, double aj1j1, double ajj1, double aj1j) {
    std::complex<double> a = 1.0;
    std::complex<double> b = -ajj - aj1j1;
    std::complex<double> c = ajj * aj1j1 - ajj1 * aj1j;

    std::complex<double> D = std::sqrt(b*b - 4.0*a*c);
    std::complex<double> x1 = (-b + D) / (2.0*a);
    std::complex<double> x2 = (-b - D) / (2.0*a);

    return std::make_pair(x1, x2);
}