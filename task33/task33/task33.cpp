// task33.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <Windows.h>
#include <psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <cstdio>
#include <tlhelp32.h>

DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile)) {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo)) {
        if (!processName.compare(processInfo.szExeFile)) {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}

int main()
{
    // Find process Id by process Name
    std::wstring processName;
    std::wcout << "Enter process name to kill (Example: Calculator.exe): ";
    std::wcin >> processName;

    DWORD processId = FindProcessId(processName);

    // Check if there is no such process among opened processes
    if (processId == 0) {
        std::wcout << "There is no process " << processName << "among opened processes." << std::endl;
        return 0;
    }

    std::cout << "Found process Id = " << processId << std::endl;
    // Find handle of process by process pid
    HANDLE processToKill = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    // Kill the process by handle process
    TerminateProcess(processToKill, 1);
    // Close process handle
    CloseHandle(processToKill);
}
