#include "gameplayHandling.hpp"
#include "graphics.hpp"
#include "ship.hpp"

#include <queue>

void HandleGameplay() {

    ships.front().HandleUserInput();

    while (!events.empty()){

        events.pop();
    }
}