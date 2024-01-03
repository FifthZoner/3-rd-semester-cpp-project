#include <iostream>
#include "gameplayRender.hpp"
#include "ship.hpp"

void RenderGameplayGame(sf::RenderWindow& window) {
    for (auto& n : ships) {
        n.draw(window);
    }
}