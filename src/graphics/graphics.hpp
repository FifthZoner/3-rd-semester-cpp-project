#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <queue>
#include <cstdint>
#include <vector>

// pass to logic loop
std::queue<sf::Event>* PrepareGraphics();

void Render();

enum Element {
    editorMain, editorListStructural
};

#endif