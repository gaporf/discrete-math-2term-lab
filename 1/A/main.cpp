#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
	std::ios_base::sync_with_stdio(false);
	freopen("exam.in", "r", stdin);
	freopen("exam.out", "w", stdout);
	size_t k;
        double n;
	long long ans = 0;
	std::cin >> k >> n;
	for (size_t i = 0; i < k; i++) {
		long long p, m;
		std::cin >> p >> m;
		ans += p * m;
	}
	std::cout << std::setprecision(10) << (double) (ans) / n / 100 << std::endl;

	return 0;
}
