#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_SHIP_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_SHIP_HPP

#include <memory>

#include "parts.hpp"
#include "editorShipPart.hpp"

struct Ship {
    std::vector <sf::Sprite> partSprites;
    // weapons here
    unsigned int power = 0;
    unsigned int drain = 0;
    unsigned int mass = 0;
    float accelerationFront = 0.f;
    float accelerationBack = 0.f;
    float accelerationRight = 0.f;
    float accelerationLeft = 0.f;
    sf::Vector2f speed = {0, 0};
    //sf::RenderTexture shipTexture;
    //sf::Sprite shipSprite;

    // returns nullptr if there was an error
    static Ship* createShip(std::vector <EditorShipPart>& parts, sf::Vector2f position);
    void HandleUserInput(sf::Event& event);
    void HandleAITick();
    Ship() = default;
    void create(std::vector <EditorShipPart>& parts, sf::Vector2f position);
    void draw(sf::RenderTexture& target) const;
    void draw(sf::RenderWindow& target) const;
};

// index 0 is always the player ship
inline std::vector <Ship> ships;

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_SHIP_HPP