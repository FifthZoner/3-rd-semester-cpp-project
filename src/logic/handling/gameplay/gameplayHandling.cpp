#include "gameplayHandling.hpp"
#include "graphics.hpp"
#include "ship.hpp"
#include "projectile.hpp"
#include "collision.hpp"

#include <queue>

void HandleGameplay() {

    ships.front().HandleUserInput();

    HandleProjectiles();

    HandleCollisions();

    while (!events.empty()){

        events.pop();
    }
}