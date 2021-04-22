// task31.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

/*
ѕод задачу создать репо, в котором в мастер ветку инитиал коммитом
пушим VS проектные файлы, после этого выводим ветку, в которую делаем реализацию.
ѕосле этого создаем пул реквест (PR) и кидаем мне.
*/


int findNonRepeatableNumber(std::vector<int>& nums) {
    bool repeatableFlag = false;
    int foundNonRepeatableNumber = -999;
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
            foundNonRepeatableNumber = nums[i];
            break;
        }
    }
    if (repeatableFlag == false) {
        throw std::runtime_error("There is no non repeatable number");
    }

    return foundNonRepeatableNumber;
}

int main()
{
    std::vector<int> numbers{ 7, 9, 1, 7, 8, 0, 9, 1, 8 };
    std::vector<int> numbersWithoutRepeatableNumber { 7, 9, 1, 7, 8, 9, 1, 8 };

    try {
        std::cout << "Non repeatable number: " << findNonRepeatableNumber(numbers) << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }


    try {
        std::cout << "Non repeatable number: " << 
            findNonRepeatableNumber(numbersWithoutRepeatableNumber) << std::endl;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}