#include <iostream>
int main() {
	int n, k;
	std::cin >> n >> k;
	int res = 0;
	for (int i = 1; i <= n; ++i)
		res = (res + k) % i;
	std::cout << res + 1;
}