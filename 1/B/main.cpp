#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

double pow(double a, double b) {
    double ans = 1;
    while (b-- > 0) {
        ans *= a;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in;
    in.open("shooter.in");
    std::ofstream out;
    out.open("shooter.out");
    size_t n, m, k;
    in >> n >> m >> k;
    std::vector<double> p(n);
    double sum = 0;
    for (size_t i = 0; i < n; i++) {
        in >> p[i];
        p[i] = pow(1 - p[i], m);
        sum += p[i];
    }
    out << std::setprecision(228) << p[--k]/sum << std::endl;
    in.close();
    out.close();

    return 0;
}