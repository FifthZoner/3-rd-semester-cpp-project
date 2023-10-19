#include <SFML/Graphics.hpp>
#include <vector>

#include "graphics.hpp"
#include "../misc/settings.hpp"


sf::RenderWindow window;

std::queue<sf::Event> events;

std::vector <uint16_t> renderVector;

std::vector <uint16_t>& AccessElementVector(){
    return renderVector;
}

std::queue<sf::Event>* PrepareGraphics(){
    window.create(sf::VideoMode(setting::Resolution().x, setting::Resolution().y, 32), "Space Game");
    window.setFramerateLimit(setting::Framerate());
    window.setActive(true);
    window.setVerticalSyncEnabled(true);
    return &events;
}

#include "elements/elements.hpp"

inline void RenderElements(){
    for (auto current : renderVector){
        switch (current){
        case Element::editorMain:
            // function here
            break;
        case Element::editorListStructural:
            //function here
            break;
        default:
            break;
        }
    }
    RenderEditor(window);
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