#include "misc.hpp"
#include "cstdint"

std::vector<std::string> SplitString(std::string string, char character){
    std::vector<std::string> vec;
    uint64_t start = 0;
    for (uint64_t n = 0; n < string.length(); n++){
        if (string[n] == character and n != 0){
            vec.push_back(string.substr(start, n - start));
            start = n + 1;
        }
    }
    if (string[string.length() - 1] != character){
        vec.push_back(string.substr(start, string.length() - start));
    }

    return vec;
}

#ifdef __WIN32__
    #define _WIN32_WINNT 0x0500
    #include <windows.h>

void HideConsole(){
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
}
#endif