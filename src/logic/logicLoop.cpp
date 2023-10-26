#include <mutex>

#include "logicLoop.hpp"
#include "../misc/settings.hpp"
#include "../graphics/classes/graphicsLib.hpp"
#include "../graphics/graphics.hpp"

#define TICKRATE 60.0

extern sf::RenderWindow window;
extern Button buttonEditorPervious, buttonEditorNext;
extern std::vector<uint16_t> renderVector;

void logicLoop(std::queue<sf::Event>* events){
    
    renderVector.push_back(Element::editorMain);
    renderVector.push_back(Element::editorListStructural);

    double tickTime = 1000000 / TICKRATE;
    sf::Clock tickClock;


    while(setting::IsRunning()){

        if (tickClock.getElapsedTime().asMicroseconds() < tickTime){
            sf::sleep(sf::microseconds(10));
            continue;
        }
        // handling events
        while (!events->empty()){

            switch (events->front().type){
                
            case sf::Event::MouseButtonPressed:
                buttonEditorNext.checkClick(sf::Mouse::getPosition(window));
                buttonEditorPervious.checkClick(sf::Mouse::getPosition(window));
                break;
            case sf::Event::MouseButtonReleased:
                buttonEditorNext.checkClick(sf::Mouse::getPosition(window));
                buttonEditorPervious.checkClick(sf::Mouse::getPosition(window));
                break;
            default:
                break;
            }

            events->pop();
        }


        // handling other things


    }

    // getting rid of things

}