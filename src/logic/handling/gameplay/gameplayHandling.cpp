#include "gameplayHandling.hpp"
#include "graphics.hpp"
#include "ship.hpp"
#include "projectile.hpp"
#include "collision.hpp"
#include "loading.hpp"

#include <queue>
#include <iostream>

void addEnemyShip() {
    Ship::createShip(shipTemplates[0], {300, 300});
}

void HandleGameplay() {

    ships.front().handleUserInput();

    for (unsigned int n = 1; n < ships.size() ;n++) {
        ships[n].handleAITick();
    }

    HandleProjectiles();

    HandleCollisions();

    while (!events.empty()){

        if (events.front().type == sf::Event::TextEntered and events.front().text.unicode == 'n') {
            addEnemyShip();
        }

        events.pop();
    }
}