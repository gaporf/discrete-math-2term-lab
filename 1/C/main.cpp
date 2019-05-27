#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream in;
    in.open("lottery.in");
    std::ofstream out;
    out.open("lottery.out");
    double N;
    size_t M;
    in >> N >> M;
    double last_b = 0;
    double ans = 0;
    double cnt = 1;
    for (size_t i = 0; i != M; i++) {
        double a, b;
        in >> a >> b;
        ans += cnt * (a - 1) / a * last_b;
        cnt *= 1 / a;
        last_b = b;
    }
    ans += cnt * last_b;
    out << std::setprecision(228) << (N - ans) << std::endl;
    in.close();
    out.close();
    return 0;
}