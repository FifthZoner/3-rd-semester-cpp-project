#ifndef MISC_HPP
#define MISC_HPP

#include <vector>
#include <string>

std::vector<std::string> SplitString(std::string string, char character);

#ifdef __WIN32__
void HideConsole();
#endif

#endif