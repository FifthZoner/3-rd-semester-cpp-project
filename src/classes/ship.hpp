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


/*#include <iostream>
#include <memory>
#include "ship.hpp"
#include "settings.hpp"

void CheckShipConnection(std::vector <std::vector <uint8_t>>& checkArray, unsigned int x, unsigned int y) {
    // 2 is the value of checked
    checkArray[x][y] = 2;

    if (x > 0 and checkArray[x - 1][y] == 1) {
        CheckShipConnection(checkArray, x - 1, y);
    }

    if (y > 0 and checkArray[x][y - 1] == 1) {
        CheckShipConnection(checkArray, x, y - 1);
    }

    if (x < checkArray.size() - 1 and checkArray[x + 1][y] == 1) {
        CheckShipConnection(checkArray, x + 1, y);
    }

    if (y < checkArray.front().size() - 1 and checkArray[x][y + 1] == 1) {
        CheckShipConnection(checkArray, x, y + 1);
    }
}

bool IsShipValid (std::vector <EditorShipPart>& parts) {

    if (parts.empty()) {
        return false;
    }

    // checking bounds
    sf::Vector2i lower = {100000, 100000};
    sf::Vector2i upper = {0, 0};

    for (auto& n : parts) {
        if (int(n.sprite.getPosition().x) / int(setting::editorScale * 32) > upper.x) {
            upper.x = int(n.sprite.getPosition().x) / int(setting::editorScale * 32);
        }
        if (int(n.sprite.getPosition().y) / int(setting::editorScale * 32) > upper.y) {
            upper.y = int(n.sprite.getPosition().y) / int(setting::editorScale * 32);
        }
        if (int(n.sprite.getPosition().x) / int(setting::editorScale * 32) < lower.x) {
            lower.x = int(n.sprite.getPosition().x) / int(setting::editorScale * 32);
        }
        if (int(n.sprite.getPosition().y) / int(setting::editorScale * 32) < lower.y) {
            lower.y = int(n.sprite.getPosition().y) / int(setting::editorScale * 32);
        }
    }

    sf::Vector2i arraySize = upper - lower + sf::Vector2i(1, 1);
    std::vector <std::vector <uint8_t>> checkArray(arraySize.x, std::vector<uint8_t>(arraySize.y, false));

    // putting elements into the vector
    for (auto& n : parts) {
        if (checkArray[int(n.sprite.getPosition().x) / int(setting::editorScale * 32) - lower.x]
        [int(n.sprite.getPosition().y) / int(setting::editorScale * 32) - lower.y]) {
            return false;
        }
        checkArray[int(n.sprite.getPosition().x) / int(setting::editorScale * 32) - lower.x]
        [int(n.sprite.getPosition().y) / int(setting::editorScale * 32) - lower.y] = true;
    }

    // checking if all ship parts are connected
    CheckShipConnection(checkArray, int(parts.front().sprite.getPosition().x) / int(setting::editorScale * 32) - lower.x,
                        int(parts.front().sprite.getPosition().y) / int(setting::editorScale * 32) - lower.y);

    // checking if any value 1 remains, all connected to first element should have value 2
    for (auto& current : checkArray) {
        for (auto& n : current) {
            if (n == 1) {
                std::cout << "Disconnected parts!\n";
                return false;
            }
            if (n == 3) {
                std::cout << "Invalid connections!\n";
            }
        }
    }

    // checking amount of types of parts
    bool engineFront = false;
    bool engineBack = false;
    bool engineRight = false;
    bool engineLeft = false;
    bool reactor = false;
    bool control = false;

    for (auto& n : parts) {
        if (n.partPointer->type() == PartType::engine) {
            switch (int(n.sprite.getRotation() / 90)) {
                case 0:
                    engineFront = true;
                    break;
                case 1:
                    engineRight = true;
                    break;
                case 2:
                    engineBack = true;
                    break;
                case 3:
                    engineLeft = true;
                    break;
            }
            continue;
        }
        if (n.partPointer->type() == PartType::reactor) {
            reactor = true;
            continue;
        }
        if (n.partPointer->type() == PartType::control) {
            control = true;
            continue;
        }
    }

    //std::cout << "Checked ship with result: " << engineBack * engineFront * engineRight * engineLeft * reactor * control << "\n";
    //std::cout << engineBack << " " << engineFront << " " << engineRight << " " << engineLeft << " " << reactor << " " << control << "\n";
    return engineBack * engineFront * engineRight * engineLeft * reactor * control;
}

Ship* Ship::createShip(std::vector <EditorShipPart>& parts, sf::Vector2f position) {

    // Will be removed after ship creation testing
    //if (!IsShipValid(parts)) {
    //    return nullptr;
    //}

    Ship* temp;
    temp->create(parts, position);
    return temp;
}

void Ship::HandleUserInput(sf::Event& event) {

}

void Ship::HandleAITick() {

}

void Ship::create(std::vector <EditorShipPart>& parts, sf::Vector2f position) {

    sf::Vector2i lower = {100000, 100000};
    sf::Vector2i upper = {0, 0};

    // checking ship size
    for (auto& n : parts) {
        if (int(n.sprite.getPosition().x) / int(setting::editorScale * 32) > upper.x) {
            upper.x = int(n.sprite.getPosition().x) / int(setting::editorScale * 32);
        }
        if (int(n.sprite.getPosition().y) / int(setting::editorScale * 32) > upper.y) {
            upper.y = int(n.sprite.getPosition().y) / int(setting::editorScale * 32);
        }
        if (int(n.sprite.getPosition().x) / int(setting::editorScale * 32) < lower.x) {
            lower.x = int(n.sprite.getPosition().x) / int(setting::editorScale * 32);
        }
        if (int(n.sprite.getPosition().y) / int(setting::editorScale * 32) < lower.y) {
            lower.y = int(n.sprite.getPosition().y) / int(setting::editorScale * 32);
        }
    }

    sf::Vector2f width = sf::Vector2f(upper) - sf::Vector2f(lower) + sf::Vector2f(1, 1);
    sf::Vector2f centerOffset = sf::Vector2f(lower) + (width / 2.f);
    sf::Vector2u size = sf::Vector2u(width) * (unsigned int)(setting::editorScale * 32);

    partSprites.resize(parts.size());

    for (unsigned int n = 0; n < parts.size(); n++) {
        parts[n].partPointer->setSprite(partSprites[n]);
        partSprites[n].setOrigin(parts[n].sprite.getPosition() - centerOffset);
        partSprites[n].setRotation(parts[n].sprite.getRotation());
        partSprites[n].setPosition(position);
    }

    // parameters here
}

void Ship::draw(sf::RenderWindow& target) const{
    for (auto& n : partSprites) {
        target.draw(n);
    }
}

void Ship::draw(sf::RenderTexture& target) const{
    for (auto& n : partSprites) {
        target.draw(n);
    }
}*/