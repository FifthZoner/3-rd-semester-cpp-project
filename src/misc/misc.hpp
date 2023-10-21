#ifndef MISC_HPP
#define MISC_HPP

#include <vector>
#include <string>

std::vector<std::string> SplitString(std::string string, char character);

#ifdef __WIN32__
void HideConsole();
#endif

// takes a path and returns a vector of split strings with irrelevant data removed and quoted strings not split
// returns an empty vector if it fails to open
std::vector<std::vector<std::string>> ParseTextFile(std::string path);

std::vector<std::string> ParseTextFileWholeLines(std::string path);

#endif