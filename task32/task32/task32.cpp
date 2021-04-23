// task32.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <atlstr.h>


class WinException: public std::exception {
public:
    WinException(int code, std::string message)
        : m_errorCode(code), m_errorMessage(message) {
    }

    const char* what() const throw () {
        return m_errorMessage.c_str();
    }

private:
    int m_errorCode;
    std::string m_errorMessage;
};

std::string GetLastErrorAsString() {
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string();
    }

    LPSTR messageBuffer = nullptr;

    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorMessageID,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer,
        0,
        NULL);

    std::string message(messageBuffer, size);

    LocalFree(messageBuffer);
    return message;
}

int fileExists(TCHAR* file)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE handle = FindFirstFile(file, &FindFileData);
    int found = handle != INVALID_HANDLE_VALUE;
    if (found) {
        FindClose(handle);
    }
    return found;
}

void createFile(const char* filePath) {
    HANDLE resource = CreateFileA(
        (LPSTR)filePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (resource == INVALID_HANDLE_VALUE) {
        CloseHandle(resource);
        throw WinException(GetLastError(), GetLastErrorAsString());
    }
    CloseHandle(resource);
}

int main() {
    TCHAR pathFrom[256] = {0};
    TCHAR pathTo[256] = {0};

    std::string pathFileFrom;
    std::string pathFileTo;

    std::cout << "Please enter path to file copy from: " << std::endl;
    std::cin >> pathFileFrom;
    _tcscpy_s(pathFrom, CA2T(pathFileFrom.c_str()));

    std::cout << "Please enter path to file copy to: " << std::endl;
    std::cin >> pathFileTo;
    _tcscpy_s(pathTo, CA2T(pathFileTo.c_str()));

    //task1
    try {
        if (fileExists(pathFrom)) {
            CopyFile(pathFrom, pathTo, TRUE);
        }
        else {
            std::cout << "File from doesn`t exist. Please try it again!" << std::endl;
        }
    }
    catch (const std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;
    }

    //task2
    try {
        createFile("C:/Users/yestS/ww/test1.txt");
    }
    catch (const WinException& ex) {
        std::cout << ex.what() << std::endl;
    }
}
