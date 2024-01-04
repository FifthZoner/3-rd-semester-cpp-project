#include <mutex>
#include <vector>

#include "logicLoop.hpp"
#include "logicStructs.hpp"
#include "handling.hpp"
#include "../misc/settings.hpp"
#include "../graphics/graphics.hpp"
#include "gameplayHandling.hpp"

#define TICK_RATE 60

extern std::queue<sf::Event> events;

void logicLoop(){
    
    renderVector.push_back(Element::editorMain);
    renderVector.push_back(Element::editorListStructural);

    logicVector.emplace_back(LogicStage::editor, true);

    long long tickTime = 1000000 / TICK_RATE;
    sf::Clock tickClock;


    while(setting::IsRunning()){

        while (tickClock.getElapsedTime().asMicroseconds() < tickTime){
            sf::sleep(sf::microseconds(10));
        }
        tickClock.restart();
        for (long n = logicVector.size() - 1; n > -1; n--){
            switch (logicVector[n].type){
                case LogicStage::editor:
                    HandleEditor();
                    break;
                case LogicStage::game:
                    HandleGameplay();
                    break;
                default:
                    break;
            }
        }


        // handling other things


    }

    // getting rid of things

}