#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

std::vector<std::vector<long double> >
multiply(std::vector<std::vector<long double> > &a, std::vector<std::vector<long double> > &b, size_t n) {
    std::vector<std::vector<long double> > ans(n);
    for (size_t i = 0; i < n; i++) {
        ans[i].resize(n, 0);
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            ans[i][j] = 0;
            for (size_t k = 0; k < n; k++) {
                ans[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return ans;
}

std::vector<std::vector<long double> > pow(std::vector<std::vector<long double>> &p, size_t n, size_t m) {
    if (m == 0) {
        std::vector<std::vector<long double> > e(n);
        for (size_t i = 0; i < n; i++) {
            e[i].resize(n);
            e[i][i] = 1;
        }
        return e;
    } else {
        std::vector<std::vector<long double> > first = pow(p, n, m / 2);
        first = multiply(first, first, n);
        if (m % 2 != 0) {
            first = multiply(first, p, n);
        }
        return first;
    }
}

bool check(std::vector<std::vector<long double> > &arr, size_t n) {
    for (size_t i = 0; i + 1 < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (std::abs(arr[i][j] - arr[i + 1][j]) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::ifstream in;
    in.open("markchain.in");
    std::ofstream out;
    out.open("markchain.out");
    size_t n;
    in >> n;
    std::vector<std::vector<long double> > p(n);
    for (size_t i = 0; i < n; i++) {
        p[i].resize(n);
        for (size_t j = 0; j < n; j++) {
            in >> p[i][j];
        }
    }
    while (!check(p, n)) {
        p = pow(p, n, 2);
    }

    for (size_t i = 0; i < n; i++) {
        out << std::setprecision(1000) << p[0][i] << " ";
    }
    out << std::endl;
    in.close();
    out.close();
    return 0;
}