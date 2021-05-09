// task36.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <windows.h>

#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>

#include "Gamble.h"

#define TWO_MINUTES 120

Gamble gamble = Gamble();

struct Arguments {
    const char* personName;
    int guessNumber;
};

DWORD WINAPI Process(LPVOID lpParameter) {
    Arguments* arguments = static_cast<Arguments*>(lpParameter);
    gamble.AddPrediction(std::string(arguments->personName), arguments->guessNumber);
    return 0;
}

WORD GetMinutesAfterDuration(int minutes) {
    SYSTEMTIME endTime;
    FILETIME ft;
    // Get local time from system
    GetLocalTime(&endTime);
    // Convert to filetime
    SystemTimeToFileTime(&endTime, &ft);
    // Add TWO_MINUTES in seconds
    ((ULARGE_INTEGER*)&ft)->QuadPart += (TWO_MINUTES * 10000000LLU);
    // Convert back to systemtime
    FileTimeToSystemTime(&ft, &endTime);
    return endTime.wMinute;
}

bool isTimeExpired(WORD wMinute) {
    SYSTEMTIME now;
    // Get local time from system
    GetLocalTime(&now);
    return now.wMinute >= wMinute;
}

int main()
{    
    WORD endTime = GetMinutesAfterDuration(TWO_MINUTES); // specially cut time structure to minutes

    std::string personName;
    int guessNumber = 0;
    DWORD threadId = 0; // TID

    while (!isTimeExpired(endTime)) {
        std::cout << "Enter your name: ";
        std::cin >> personName;
        std::cout << "Enter guess number: ";
        std::cin >> guessNumber;

        Arguments args = { personName.c_str(), guessNumber };
        std::make_shared<HANDLE>(CreateThread(
           0,
           0,
           Process,
           &args,
           0,
           &threadId));
    }

    std::pair<std::string, int> winner = gamble.GetWinner();
    std::cout << "Winner: " << winner.first << " with guess number: " << winner.second << std::endl;
}