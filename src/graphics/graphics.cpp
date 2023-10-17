#include <SFML/Graphics.hpp>

#include "graphics.hpp"
#include "../misc/settings.hpp"

uint16_t stage = 0;

sf::RenderWindow window;

std::queue<sf::Event> events;

std::queue<sf::Event>* PrepareGraphics(){
    window.create(sf::VideoMode(setting::Resolution().x, setting::Resolution().y, 32), "Space Game");
    window.setFramerateLimit(setting::Framerate());
    window.setActive(true);
    window.setVerticalSyncEnabled(true);
    return &events;
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


    window.display();
}

void SetStage(uint16_t value){
    stage = value;
}

uint16_t GetStage(){
    return stage;
}