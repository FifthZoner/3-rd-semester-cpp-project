#include "misc.hpp"
#include <cstdint>
#include <fstream>

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

std::vector<std::string> SplitLine(std::string string){
    std::vector<std::string> vec;

    // checking for unenclosed quotes, skipped if this is a case
    uint16_t quotes = 0;
    for (char next : string){
        if (next == '\"'){
            quotes++;
        }
    }
    if (quotes % 2 != 0){
        return vec;
    }
    quotes /= 2;

    uint64_t start = 0;
    for (uint64_t n = 0; n < string.length(); n++){
        if (string[n] == ' ' and n != 0){
            vec.push_back(string.substr(start, n - start));
            start = n + 1;
        }
        else if (string[n] == '\"'){
            
            n++;
            start = n;
            for (;string[n] != '\"'; n++){}
            vec.push_back(string.substr(start, n - start));
            // adds enough for n to get into the next argument if there's any
            n += 2;
            start = n;
        }
    }

    if (string[string.length() - 1] != ' ' and quotes == 0){
        vec.push_back(string.substr(start, string.length() - start));
    }

    return vec;
}

std::vector<std::vector<std::string>> ParseTextFile(std::string path){
    std::vector <std::vector <std::string> > vec;
    std::ifstream file;
    file.open(path);

    if (!file.is_open()){
        return vec;
    }

    while (!file.eof()){
        std::string input;
        std::getline(file, input);

        if (input.length() > 0 and input[0] == '#'){
            continue;
        }

        auto temp = SplitLine(input);
        if (temp.size() > 0){
            vec.push_back(temp);
        }
        
    }

    return vec;
}

std::vector<std::string> ParseTextFileWholeLines(std::string path){
    std::vector <std::string> vec;
    std::ifstream file;
    file.open(path);

    if (!file.is_open()){
        return vec;
    }

    while (!file.eof()){
        std::string input;
        std::getline(file, input);

        if (input.length() > 0 and input[0] == '#'){
            continue;
        }

        vec.push_back(input);
    }

    return vec;
}