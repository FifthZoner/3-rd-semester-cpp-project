#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <queue>
#include <cstdint>
#include <vector>

// pass to logic loop
std::queue<sf::Event>* PrepareGraphics();

void Render();

// this vector contains the data for the renderer about what to draw
std::vector <uint16_t>& AccessElementVector();

enum Element {
    editorMain, editorListStructural
};

#endif