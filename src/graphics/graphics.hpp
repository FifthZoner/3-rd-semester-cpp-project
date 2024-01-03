#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <queue>
#include <cstdint>
#include <vector>

inline std::vector <uint16_t> renderVector;

void PrepareGraphics();

void Render();

enum Element {
    editorMain, editorListStructural, gameplayGame
};

#endif