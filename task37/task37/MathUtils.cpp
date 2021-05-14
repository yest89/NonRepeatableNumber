
#include "MathUtils.h"


long MathUtils::multiply(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
	int total = 0;
	for (auto it = begin; it != end; ++it) {
		total += *it;
	}
	return total;
}

long MathUtils::fibonaci(int n) {
	if (n <= 1)
		return n;
	else {
		return fibonaci(n - 1) + fibonaci(n - 2);
	}
}