#include <thread>
#include <iostream>

#include "logic/logicLoop.hpp"
#include "graphics/graphicsLoop.hpp"
#include "misc/settings.hpp"
#include "misc/misc.hpp"

int main(int, char**){

    #ifdef __WIN32__
    HideConsole();
    #endif

    // load settings here
    if (!setting::LoadSettings("data/settings.cfg")){
        std::cout << "Settings were not loaded successfully! Please check the settings file for issues.\n";
    }

    std::queue<sf::Event> events;

    std::thread logicThread = std::thread(logicLoop, &events);

    // graphics loop

    logicThread.join();

    return 0;
}
