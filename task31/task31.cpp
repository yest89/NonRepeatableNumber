// task31.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::pair<bool, int> findNonRepeatableNumber(std::vector<int>& nums) {
    bool repeatableFlag = false;
    std::pair<bool, int> foundNonRepeatableNumber{};
    for (int i = 0; i < nums.size(); i++) {
        repeatableFlag = true;
        for (int j = 0; j < nums.size(); j++) {
            if (i == j) {
                continue;
            }
            if (nums[i] == nums[j]) {
                repeatableFlag = false;
                break;
            }
        }

        if (repeatableFlag == 1) {
            foundNonRepeatableNumber = { repeatableFlag, nums[i] };
            break;
        }
    }
    return foundNonRepeatableNumber;
}

unsigned nCr(unsigned n, unsigned k) // combination calculation
{
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    int result = n;
    for (int i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

int main()
{
    std::vector<int> numbers{ 7, 9, 1, 7, 8, 0, 9, 1, 8 };
    std::vector<int> numbersWithoutRepeatableNumber{ 7, 9, 1, 7, 8, 9, 1, 8 };

    std::pair<bool, int> nonRepeatableNumber = findNonRepeatableNumber(numbers);
    std::pair<bool, int> noNonRepeatableNumber = 
        findNonRepeatableNumber(numbersWithoutRepeatableNumber);

    if (nonRepeatableNumber.first) {
        std::cout << "Non repeatable number: " << nonRepeatableNumber.second << std::endl;
    }
    else {
        std::cout << "There is no non repeatable number: " << std::endl;
    }

    if (noNonRepeatableNumber.first) {
        std::cout << "Non repeatable number: " << noNonRepeatableNumber.second << std::endl;
    }
    else {
        std::cout << "There is no non repeatable number: " << std::endl;
    }

    int n = 10;
    int counterTo = ((2 * n) + 1);
    int counterFrom = n + 1;
    int result = 0;
    for(int a = counterFrom; a < counterTo; a++) {
        int temp = (((2 * a) - (2 * n) - 1) / counterTo);
        int combination = nCr(counterTo, counterFrom);
        result += (temp*combination);
    }
    std::cout << result << std::endl;
}

