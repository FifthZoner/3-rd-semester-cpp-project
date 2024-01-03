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
    sf::Sprite partSprite;

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

    shipTexture.create(size.x, size.y);
    shipTexture.clear(sf::Color::Transparent);

    // drawing the sprites into RenderTexture
    for (auto& n : parts) {
        n.partPointer->setSprite(partSprite);
        partSprite.setOrigin(n.sprite.getPosition() - centerOffset);
        partSprite.setRotation(n.sprite.getRotation());
        partSprite.setPosition(position);
        shipTexture.draw(partSprite);
    }

    shipTexture.display();
    shipSprite.setTexture(shipTexture.getTexture());
    shipSprite.setOrigin(shipSprite.getGlobalBounds().getSize() / 2.f);
    shipSprite.setPosition(position);
}

void Ship::draw(sf::RenderWindow& target) const{
    target.draw(shipSprite);
}

void Ship::draw(sf::RenderTexture& target) const{
    target.draw(shipSprite);
}*/

#include <iostream>
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

    partSprites.resize(1);

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
}