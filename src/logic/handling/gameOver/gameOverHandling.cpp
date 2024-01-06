#include "gameOverHandling.hpp"
#include "graphics.hpp"

void HandleGameOver() {
    // there's nothing, you lost

    while (!events.empty()){
        events.pop();
    }
}