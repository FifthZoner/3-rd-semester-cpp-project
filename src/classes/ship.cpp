#include <iostream>
#include <memory>
#include "ship.hpp"
#include "settings.hpp"
#include "editorHandling.hpp"
#include "gameplayHandling.hpp"
#include "graphics.hpp"
#include "projectile.hpp"
#include "aux.hpp"
#include "collision.hpp"
#include <cmath>

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

bool Ship::createShip(std::vector <EditorShipPart>& parts, sf::Vector2f position) {

    // Will be removed after ship creation testing
    //if (!IsShipValid(parts)) {
    //    return false;
    //}

    while (editorElementLock){
        sf::sleep(sf::microseconds(10));
    }
    editorElementLock = true;
    while (gameplayElementLock){
        sf::sleep(sf::microseconds(10));
    }
    gameplayElementLock = true;
    ships.clear();
    ships.emplace_back(parts, position);
    editorElementLock = false;
    gameplayElementLock = false;

    return true;
}

#define MAX_SHIP_ROTATION_SPEED 2.4f
#define MAX_SHIP_VELOCITY 600.f

void Ship::HandleUserInput() {

    sf::Vector2f tempSpeed = speed;

    // acceleration
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        speed.x += std::sin(partSprites.front().getRotation() * 0.017452778f) * accelerationFront;
        speed.y -= std::cos(partSprites.front().getRotation() * 0.017452778f) * accelerationFront;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        speed.x += std::cos(partSprites.front().getRotation() * 0.017452778f) * accelerationRight;
        speed.y += std::sin(partSprites.front().getRotation() * 0.017452778f) * accelerationRight;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        speed.x -= std::sin(partSprites.front().getRotation() * 0.017452778f) * accelerationBack;
        speed.y += std::cos(partSprites.front().getRotation() * 0.017452778f) * accelerationBack;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        speed.x -= std::cos(partSprites.front().getRotation() * 0.017452778f) * accelerationLeft;
        speed.y -= std::sin(partSprites.front().getRotation() * 0.017452778f) * accelerationLeft;
    }

    // speed limit enforcement
    if (GetDistance(sf::Vector2f(0, 0), speed) > MAX_SHIP_VELOCITY) {
        speed = tempSpeed;
    }

    // rotation
    angularSpeed += (float(sf::Mouse::getPosition(window).x) - (float(setting::Resolution().x) / 2.f)) / float(setting::Resolution().x) * accelerationRotation * 100.f;
    if (angularSpeed > MAX_SHIP_ROTATION_SPEED) {
        angularSpeed = MAX_SHIP_ROTATION_SPEED;
    }
    else if (angularSpeed < -MAX_SHIP_ROTATION_SPEED) {
        angularSpeed = -MAX_SHIP_ROTATION_SPEED;
    }
    coords = partSprites.front().getPosition() + speed / 60.f;
    rotation += angularSpeed;
    rotation = std::fmod(rotation, 360.f);
    setRotation(rotation);
    setPosition(coords);

    // shooting
    for (auto& n : weapons) {
        if (n.reloadLeft > 0) {
            n.reloadLeft--;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            // shot
            sf::Vector2f offset = n.spritePointer->getOrigin() - sf::Vector2f(16.f, 16.f);
            float distance = GetDistance(offset, {0.f,0.f});
            float angle = std::asin(-offset.x / distance);
            if (offset.y < 0.f) {
                angle = 3.1415f - angle;
            }
            angle += rotation * 0.017452778f;
            offset.x = std::sin(angle) * distance;
            offset.y = -std::cos(angle) * distance;
            AddProjectile(offset + coords, rotation, n.partPointer);
            n.reloadLeft = n.partPointer->getReloadTime();
        }
    }

    // debug shortcuts
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
        speed = {0.f, 0.f};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        angularSpeed = 0.f;
    }

    for (auto& n : asteroids) {
        if (DoesCollide(n, *this)) {
            std::cout << "Collides!\n";
        }
    }
}

void Ship::HandleAITick() {

}

Ship::Ship(std::vector <EditorShipPart>& parts, sf::Vector2f position) {

    sf::Vector2i lower = {100000, 100000};
    sf::Vector2i upper = {0, 0};

    std::vector <sf::Vector2f> coords;

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

        coords.emplace_back(int(n.sprite.getPosition().x) / int(setting::editorScale * 32),int(n.sprite.getPosition().y) / int(setting::editorScale * 32));
    }

    sf::Vector2f width = sf::Vector2f(upper) - sf::Vector2f(lower) + sf::Vector2f(1, 1);

    partSprites.resize(parts.size());

    for (unsigned int n = 0; n < parts.size(); n++) {
        parts[n].partPointer->setSprite(partSprites[n], uint8_t(parts[n].sprite.getRotation() / 90));
        partSprites[n].setOrigin((partSprites[n].getLocalBounds().width / 2) - ((coords[n].x - float(lower.x) - (width.x / 2.f)) * 32 + 16),
                                 (partSprites[n].getLocalBounds().height / 2) - ((coords[n].y - float(lower.y) - (width.y / 2.f)) * 32) - 16);

        partSprites[n].setPosition(position);
    }

    float thrustFront = 0;
    float thrustRight = 0;
    float thrustBack = 0;
    float thrustLeft = 0;

    // parameters here
    for (unsigned int n = 0; n < parts.size(); n++) {
        weight += parts[n].partPointer->getWeight();
        health += parts[n].partPointer->getHealth();

        switch (parts[n].partPointer->type()) {

            case PartType::engine:
                drain += reinterpret_cast<ShipEngine*> (parts[n].partPointer)->getDrain();
                switch (int(parts[n].sprite.getRotation() / 90)) {
                    case 0:
                        thrustFront += reinterpret_cast<ShipEngine*> (parts[n].partPointer)->getThrust();
                        break;
                    case 1:
                        thrustRight += reinterpret_cast<ShipEngine*> (parts[n].partPointer)->getThrust();
                        break;
                    case 2:
                        thrustBack += reinterpret_cast<ShipEngine*> (parts[n].partPointer)->getThrust();
                        break;
                    case 3:
                        thrustLeft += reinterpret_cast<ShipEngine*> (parts[n].partPointer)->getThrust();
                        break;
                }
                break;

            case PartType::reactor:
                power += reinterpret_cast<ShipReactor*> (parts[n].partPointer)->getPower();
                break;

            case PartType::weapon:
                weapons.emplace_back();
                weapons.back().partPointer = reinterpret_cast<ShipWeapon*> (parts[n].partPointer);
                weapons.back().spritePointer = &partSprites[n];
                break;

        }
    }
    accelerationFront = thrustFront / float(weight) * 1000.f;
    accelerationRight = thrustRight / float(weight) * 1000.f;
    accelerationBack = thrustBack / float(weight) * 1000.f;
    accelerationLeft = thrustLeft / float(weight) * 1000.f;
    accelerationRotation = float(power - drain) / float(power) / 1000.f;
    this->coords = position;
    if (width.x > width.y) {
        collisionRadius = width.x * 16.f;
    }
    else {
        collisionRadius = width.y * 16.f;
    }
    maxHealth = health;

    //std::cout << "Created a ship with accelerations: " << accelerationFront << " " << accelerationRight << " " << accelerationBack << " " << accelerationLeft << "\n";
    //std::cout << "Mass: " << weight << "\n";
    //std::cout << "Power: " << power << "\n";
    //std::cout << "Drain: " << drain << "\n";
    //std::cout << "Health: " << health << "\n";
    //std::cout << "Rotation: " << accelerationRotation << "\n";
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

void Ship::setPosition(sf::Vector2f position) {
    for (auto& n : partSprites) {
        n.setPosition(position);
    }
}

void Ship::setRotation(float rotation) {
    for (auto& n : partSprites) {
        n.setRotation(rotation);
    }
}