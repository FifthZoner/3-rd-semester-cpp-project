#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <queue>
#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>

inline sf::RenderWindow window;
inline std::vector <uint16_t> renderVector;
inline std::queue<sf::Event> events;
inline sf::Vector2f* gameplayCameraPosition = nullptr;
inline float* gameplayCameraRotation = nullptr;

void PrepareGraphics();

void Render();

enum Element {
    editorMain, editorListStructural, gameplayGame
};

#endif