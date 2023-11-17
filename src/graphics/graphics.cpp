#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

#include "graphics.hpp"
#include "../misc/settings.hpp"
#include "../misc/misc.hpp"

sf::RenderWindow window;

std::queue<sf::Event> events;

std::vector <uint16_t> renderVector;

std::string GetWindowName(){
    auto vec = ParseTextFileWholeLines("data/other/windownames.list");
    if (vec.size() == 0){
        return "I'm a generic name!";
    }
    else {
        srand(time(NULL));
        return vec[rand() % vec.size()];
    }
}

void PrepareGraphics(){

    std::string name = GetWindowName();
    window.create(sf::VideoMode(setting::Resolution().x, setting::Resolution().y, 32), name);
    window.setFramerateLimit(setting::Framerate());
    window.setActive(true);
    window.setVerticalSyncEnabled(true);
}

#include "elements/elements.hpp"

inline void RenderElements(){
    for (auto current : renderVector){
        switch (current){
        case Element::editorMain:
            RenderEditorMain(window);
            break;
        case Element::editorListStructural:
            RenderEditorList(window);
            break;
        default:
            break;
        }
    }
}

void Render(){

    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type != sf::Event::Closed){
            events.push(event);
            continue;
        }
        window.close();
        setting::IsRunning(false);        
    }
    

    window.clear();

    RenderElements();

    window.display();
}