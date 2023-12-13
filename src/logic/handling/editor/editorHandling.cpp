#include <SFML/Graphics.hpp>
#include <queue>

#include "editorHandling.hpp"
#include "../graphics/classes/graphicsLib.hpp"

extern std::queue <sf::Event> events;

bool anythingClicked = false;

uint16_t whatClicked;

extern Button buttonEditorPervious, buttonEditorNext;
extern Frame frameEditorStructuralText;
extern ScrollList scrollListEditorElements;

enum EditorClickables{
    pervious, next, list
};

void HandleEditorPressed(){
    if (buttonEditorNext.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
        whatClicked = EditorClickables::next;
        anythingClicked = true;
        return;
    }
    if (buttonEditorPervious.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
        whatClicked = EditorClickables::pervious;
        anythingClicked = true;
        return;
    }
    if (scrollListEditorElements.isClicked(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
        whatClicked = EditorClickables::list;
        anythingClicked = true;
        return;
    }
}

void HandleEditorReleased(){
    switch (whatClicked){
        case EditorClickables::next:
            if (buttonEditorNext.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
                scrollListEditorElements.nextList();
            }
        break;

        case EditorClickables::pervious:
            if (buttonEditorPervious.checkClick(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
                scrollListEditorElements.perviousList();
            }
        break;

        case EditorClickables::list:
            if (scrollListEditorElements.isClicked(sf::Vector2i(events.front().mouseButton.x, events.front().mouseButton.y))){
                // reacting to clicking an element
            }
        break;
    }
}

void HandleEditor(){
    while (events.size()){
        switch (events.front().type){
            case sf::Event::MouseButtonPressed:
                HandleEditorPressed();
            break;

            case sf::Event::MouseButtonReleased:
                if (anythingClicked){
                    anythingClicked = false;
                    HandleEditorReleased();
                }
            break;

            default:
            break;
        }
        events.pop();
    }
}