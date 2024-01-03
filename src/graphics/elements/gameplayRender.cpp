#include <iostream>
#include "gameplayRender.hpp"
#include "ship.hpp"
#include "gameplayHandling.hpp"

void RenderGameplayGame(sf::RenderWindow& window) {
    while (gameplayElementLock){
        sf::sleep(sf::microseconds(5));
    }
    gameplayElementLock = true;
    for (auto& n : ships) {
        n.draw(window);
    }
    gameplayElementLock = false;
}