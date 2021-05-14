// task37.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <future>

#include "MathUtils.h"

int main() {
    std::vector<int> vc;
    for (int i = 1; i <= 15; i++)
        vc.push_back(i);

    int numberForFibonaci = 7;

    std::future<long> multiplicationResult = std::async(MathUtils::multiply, vc.begin(), vc.end());
    std::future<long> fibonaciResult = std::async(MathUtils::fibonaci, numberForFibonaci);

    std::cout << "Multiplication Result = " << multiplicationResult.get() << std::endl;
    std::cout << "Fibonaci Result = " << fibonaciResult.get() << std::endl;
}