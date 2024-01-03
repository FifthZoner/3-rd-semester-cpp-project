#include <SFML/Graphics.hpp>
#include <queue>
#include <iostream>

#include "editorHandling.hpp"
#include "editorShipPart.hpp"
#include "../graphics/classes/graphicsLib.hpp"
#include "../../../graphics/elements/editorRender.hpp"
#include "../../../classes/ship.hpp"
#include "logicLoop.hpp"
#include "graphics.hpp"

extern std::queue <sf::Event> events;

uint16_t whatClicked = 0;
EditorShipPart* clickedEditorPart = nullptr;

enum EditorClickables{
    none, previous, next, list, part, start
};

void HandleEditorPressed(){
    if (buttonEditorNext.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
        whatClicked = EditorClickables::next;
        return;
    }
    if (buttonEditorPrevious.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
        whatClicked = EditorClickables::previous;
        return;
    }
    if (buttonEditorStart.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
        whatClicked = EditorClickables::start;
        return;
    }
    if (scrollListEditorElements.isClicked(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
        whatClicked = EditorClickables::list;
        return;
    }
    for (auto& n : editorParts) {
        if (n.isClicked(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))) {
            clickedEditorPart = &n;
            whatClicked = EditorClickables::part;
            return;
        }
    }
}

void HandleEditorReleased(){
    switch (whatClicked){
        case EditorClickables::next:
            if (buttonEditorNext.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
                scrollListEditorElements.nextList();
            }
        break;

        case EditorClickables::previous:
            if (buttonEditorPrevious.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
                scrollListEditorElements.perviousList();
            }
        break;

        case EditorClickables::start:
            if (buttonEditorStart.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
                //auto temp = Ship::createShip(editorParts, sf::Vector2f(setting::Resolution()) / 2.f);
                //if (temp != nullptr) {
                    while (editorElementLock){
                        sf::sleep(sf::microseconds(10));
                    }
                    editorElementLock = true;
                    ships.clear();
                    ships.emplace_back();
                    ships.back().create(editorParts, sf::Vector2f(setting::Resolution()) / 2.f);
                    logicVector.clear();
                    logicVector.emplace_back(LogicStage::game, false);
                    renderVector.clear();
                    renderVector.push_back(Element::gameplayGame);
                    editorElementLock = false;
                //}
            }

            break;

        case EditorClickables::list:
            if (scrollListEditorElements.isClicked(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
                while (editorElementLock){
                    sf::sleep(sf::microseconds(10));
                }
                editorElementLock = true;
                editorParts.emplace_back(reinterpret_cast<ShipPart*>(scrollListEditorElements.getLastTileClicked()), sf::Vector2f(setting::Resolution() / 4));
                editorElementLock = false;
            }
        break;

        case EditorClickables::part:
            clickedEditorPart = nullptr;
        break;

        default:
        break;
    }
}

void EditorDeletePart(){
    while (editorElementLock){
        sf::sleep(sf::microseconds(10));
    }
    editorElementLock = true;
    for (unsigned int n = 0; n < editorParts.size(); n++) {
        if (&editorParts[n] == clickedEditorPart) {
            editorParts.erase(editorParts.begin() + n);
            editorElementLock = false;
            return;
        }
    }
    editorElementLock = false;
}

void HandleEditor(){
    while (!events.empty()){
        switch (events.front().type){
            case sf::Event::MouseButtonPressed:
                HandleEditorPressed();
                break;

            case sf::Event::MouseButtonReleased:
                if (whatClicked){
                    HandleEditorReleased();
                    whatClicked = EditorClickables::none;
                }
                break;

            case sf::Event::MouseMoved:
                if (whatClicked == EditorClickables::part) {
                    clickedEditorPart->move(sf::Vector2f(float(events.front().mouseMove.x), float(events.front().mouseMove.y)), true);
                }
                break;

            case sf::Event::TextEntered:
                if (whatClicked == EditorClickables::part) {
                   switch(toupper(int(events.front().text.unicode))) {
                       case 'Q':
                           clickedEditorPart->rotate(-1);
                       break;
                       case 'E':
                           clickedEditorPart->rotate(1);
                           break;
                       case 8:
                       case 127:
                           EditorDeletePart();
                           whatClicked = EditorClickables::none;
                           break;
                       default:
                       break;
                   }
                }
            break;

            default:
            break;
        }
        events.pop();
    }
}