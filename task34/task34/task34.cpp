// task34.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <string.h>

DWORD WINAPI PrintCurrentTime(LPVOID threadParameter) {
    SYSTEMTIME st, lt;
    while (true) {
        Sleep(5000); // 5 sec
        GetLocalTime(&lt);
        std::cout << "The current time is: " << lt.wHour << ":" << lt.wMinute <<  ":" << lt.wSecond << std::endl;
    }
    return 0;
}

const char* GetWinEnv(const char* name) {
    const DWORD buffSize = 65535;
    static char buffer[buffSize];
    if (GetEnvironmentVariableA(name, buffer, buffSize)) {
        return buffer;
    }
    else {
        return 0;
    }
}

int main(int argc, char* argv[]) {
    const char* timer = GetWinEnv("STOP_TIME");
    if (!timer) {
        std::cout << "There is no enviroment variable STOP_TIME. Please set it." << std::endl;
        return 0;
    }
    DWORD timeWhenToStop = atoi(timer)*1000;
    DWORD threadId = 0; // TID

    std::shared_ptr<HANDLE> thread = std::make_shared<HANDLE>(CreateThread(
        0,
        0,
        PrintCurrentTime,
        0,
        0,
        &threadId
    ));
    
    while (WaitForSingleObject(*thread.get(), timeWhenToStop) == WAIT_TIMEOUT) { //aka join
        TerminateThread(*thread.get(), 0);
        break;
    }
}