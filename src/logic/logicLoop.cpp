#include <mutex>
#include <vector>

#include "logicLoop.hpp"
#include "logicStructs.hpp"
#include "handling.hpp"
#include "../misc/settings.hpp"
#include "../graphics/classes/graphicsLib.hpp"
#include "../graphics/graphics.hpp"

#define TICKRATE 60.0

std::vector <LogicStage> logicVector;

extern std::vector<uint16_t> renderVector;

extern std::queue<sf::Event> events;

void logicLoop(){
    
    renderVector.push_back(Element::editorMain);
    renderVector.push_back(Element::editorListStructural);

    logicVector.push_back(LogicStage(LogicStage::editor, true));

    double tickTime = 1000000 / TICKRATE;
    sf::Clock tickClock;


    while(setting::IsRunning()){

        if (tickClock.getElapsedTime().asMicroseconds() < tickTime){
            sf::sleep(sf::microseconds(10));
            continue;
        }
        for (int8_t n = logicVector.size() - 1; n > -1; n--){
            switch (logicVector[n].type){
                case LogicStage::editor:
                    HandleEditor();
                    break;

                default:
                    break;
            }
        }


        // handling other things


    }

    // getting rid of things

}