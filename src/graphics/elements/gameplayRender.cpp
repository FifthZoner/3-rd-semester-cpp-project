#include <iostream>
#include "gameplayRender.hpp"
#include "ship.hpp"
#include "gameplayHandling.hpp"
#include "projectile.hpp"

void RenderGameplayGame(sf::RenderWindow& window) {

    while (gameplayProjectileLock){
        sf::sleep(sf::microseconds(5));
    }
    gameplayProjectileLock = true;
    for (auto& n : projectiles) {
        window.draw(n.sprite);
    }
    gameplayProjectileLock = false;

    while (gameplayElementLock){
        sf::sleep(sf::microseconds(5));
    }
    gameplayElementLock = true;
    for (auto& n : ships) {
        n.draw(window);
    }
    gameplayElementLock = false;

}