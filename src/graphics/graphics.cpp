#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <array>

#include "graphics.hpp"
#include "../misc/settings.hpp"
#include "../misc/misc.hpp"
#include "graphicsLib.hpp"


sf::View view;

sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;

std::string GetWindowName(){
    auto vec = ParseTextFileWholeLines("data/other/windownames.list");
    if (vec.size() == 0){
        return "I'm a generic name!";
    }
    else {
        srand(time(nullptr));
        return vec[rand() % vec.size()];
    }
}

void PrepareGraphics(){

    std::string name = GetWindowName();
    window.create(sf::VideoMode(setting::Resolution().x, setting::Resolution().y, 32), name);
    window.setFramerateLimit(setting::Framerate());
    window.setActive(true);
    window.setVerticalSyncEnabled(true);
    view.setSize(sf::Vector2f(setting::Resolution()));
    view.setCenter(sf::Vector2f(setting::Resolution()) / 2.f);
    backgroundTexture.loadFromFile("data/textures/spaceBackground.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setOrigin(backgroundSprite.getGlobalBounds().getSize() / 2.f);

}

#include "elements/elements.hpp"
#include "gameplayRender.hpp"
#include "logicLoop.hpp"
#include "gameOverRenderer.hpp"

inline void RenderElements(){
    for (auto current : renderVector){
        switch (current){
        case Element::editorMain:
            RenderEditorMain(window);
            break;
        case Element::editorListStructural:
            RenderEditorList(window);
            break;
        case Element::gameplayGame:
            RenderGameplayGame(window);
            break;
        case Element::gameOver:
            RenderGameOver(window);
            break;
        default:
            break;
        }
    }
}

void Render(){

    sf::Event event{};
    while (window.pollEvent(event)){
        if (event.type != sf::Event::Closed){
            events.push(event);
            continue;
        }
        window.close();
        setting::IsRunning(false);        
    }

    window.clear();

    if (!logicVector.empty() and logicVector.front().type == LogicStage::game) {
        view.setCenter(*gameplayCameraPosition);
        view.setRotation(*gameplayCameraRotation);
        backgroundSprite.setPosition(*gameplayCameraPosition);
    }
    else {
        view.setCenter(sf::Vector2f(setting::Resolution()) / 2.f);
        backgroundSprite.setPosition(sf::Vector2f(setting::Resolution()) / 2.f);
        view.setRotation(0);
    }

    // off for testing
    window.setView(view);

    window.draw(backgroundSprite);

    RenderElements();

    window.display();
}