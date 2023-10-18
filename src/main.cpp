#include <thread>
#include <iostream>

#include "logic/logicLoop.hpp"
#include "graphics/graphics.hpp"
#include "misc/settings.hpp"
#include "misc/misc.hpp"
#include "misc/loading.hpp"

int main(int, char**){

    #ifdef __WIN32__
    HideConsole();
    #endif

    // load settings here
    if (!setting::LoadSettings("data/settings.cfg")){
        std::cout << "Settings were not loaded successfully! Please check the settings file for issues.\n";
    }

    DataContainer data = LoadGame();

    std::thread logicThread = std::thread(logicLoop, PrepareGraphics());

    // graphics loop
    while (setting::IsRunning()){
        Render();
    }

    logicThread.join();

    return 0;
}
