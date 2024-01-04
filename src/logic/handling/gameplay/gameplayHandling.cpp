#include "gameplayHandling.hpp"
#include "graphics.hpp"
#include "ship.hpp"
#include "projectile.hpp"

#include <queue>

void HandleGameplay() {

    ships.front().HandleUserInput();

    HandleProjectiles();

    while (!events.empty()){

        events.pop();
    }
}