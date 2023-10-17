#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <queue>
#include <cstdint>

// pass to logic loop
std::queue<sf::Event>* PrepareGraphics();

void Render();

void SetStage(uint16_t value);
uint16_t GetStage();

#endif