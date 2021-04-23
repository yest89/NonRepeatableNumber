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
}