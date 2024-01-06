#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_SHIP_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_SHIP_HPP

#include <memory>

#include "parts.hpp"
#include "editorShipPart.hpp"
#include "healthBar.hpp"

struct Ship {
    struct WeaponContainer {
        ShipWeapon* partPointer;
        sf::Sprite* spritePointer;
        unsigned int reloadLeft = 0;
    };

    std::vector <WeaponContainer> weapons;

    std::vector <sf::Sprite> partSprites;
    // weapons here
    unsigned int power = 0;
    unsigned int drain = 0;
    unsigned int weight = 0;
    int health = 0;
    int maxHealth = 0;
    float accelerationFront = 0.f;
    float accelerationBack = 0.f;
    float accelerationRight = 0.f;
    float accelerationLeft = 0.f;
    float accelerationRotation = 0.f;
    sf::Vector2f speed = {0.f, 0.f};
    float angularSpeed = 0.f;
    float collisionRadius = 0.f;
    sf::Vector2f coords = {0, 0};
    float rotation = 0.f;
    unsigned int id = 0;
    static unsigned int ids;
    HealthBar healthBar;

    volatile bool shipDrawLock = false;

    static bool createShip(std::vector <EditorShipPart>& parts, sf::Vector2f position);
    void HandleUserInput();
    void HandleAITick();
    Ship(std::vector <EditorShipPart>& parts, sf::Vector2f position);
    void draw(sf::RenderTexture& target);
    void draw(sf::RenderWindow& target);
    void setPosition(sf::Vector2f position);
    void setRotation(float rotation);
};

// index 0 is always the player ship
inline std::vector <Ship> ships;

void DealDamageToShip(int damage, unsigned int index);

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_SHIP_HPP