#pragma once
#include <vector>

class MathUtils {
public:
	static long multiply(std::vector<int>::iterator begin, std::vector<int>::iterator end);
	static long fibonaci(int n);
private:
	MathUtils();
};