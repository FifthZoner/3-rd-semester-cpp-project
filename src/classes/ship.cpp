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
#include "logicLoop.hpp"
#include <cmath>

unsigned int Ship::ids = 1;

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
    ships.emplace_back(parts, position);
    editorElementLock = false;
    gameplayElementLock = false;

    return true;
}

#define MAX_SHIP_ROTATION_SPEED 2.4f
#define MAX_SHIP_VELOCITY 600.f

void Ship::handleUserInput() {

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
    coords = coords + speed / 60.f;
    rotation = std::fmod(rotation + angularSpeed, 360.f);
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
            AddProjectile(offset + coords, rotation, n.partPointer, id);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        coords = {0.f, 0.f};
    }
}

#define AI_SLOW_ANGLE 0.6f
#define AI_SLOW_SPEED 0.6f
#define AI_STOP_ANGLE 0.05f
#define AI_SAFE_DISTANCE 800.f
#define AI_PANIC_DISTANCE 300.f
#define AI_CRUISING_SPEED 600.f
#define AI_SAFE_DISTANCE_SPEED 150.f

void Ship::handleAITick() {

    // rotating towards player

    // get angle to player in radians
    float angle = GetRotationRelativeRadians(coords, ships.front().coords) - (rotation * 0.017452778f);
    if (angle > 3.1415f) {
        angle -= 2.f * 3.1415f;
    }
    // if below slow angle slow down to the slow speed
    if (std::abs(angle) < AI_SLOW_ANGLE) {

        // if below stop angle slow down to a stop
        if (std::abs(angle) < AI_STOP_ANGLE) {
            if (angularSpeed > 0) {
                angularSpeed -= accelerationRotation * 100.f;
            }
            else if (angularSpeed < 0) {
                angularSpeed += accelerationRotation * 100.f;
            }
        }
        else if (angularSpeed > AI_SLOW_SPEED) {
            angularSpeed -= accelerationRotation * 100.f;
        }
        else if (angularSpeed < -AI_SLOW_SPEED) {
            angularSpeed += accelerationRotation * 100.f;
        }
        else {
            if (angle < 0) {
                angularSpeed -= accelerationRotation * 100.f;
            }
            else if (angle > 0) {
                angularSpeed += accelerationRotation * 100.f;
            }
        }
    }
    // if above accelerate full speed towards player
    else {
        if (angle > 0) {
            if (angularSpeed < MAX_SHIP_ROTATION_SPEED) {
                angularSpeed += accelerationRotation * 100.f;
            }
        }
        else {
            if (angularSpeed > -MAX_SHIP_ROTATION_SPEED) {
                angularSpeed -= accelerationRotation * 100.f;
            }
        }
    }

    bool isPanicking = false;

    // moving towards player with asteroid avoidance
    for (auto& n : asteroids) {
        float distance = GetDistance(coords, n.getPosition());
        if (distance < AI_SAFE_DISTANCE + (n.getLocalBounds().width / 2)) {
            isPanicking = true;
            if (distance < AI_PANIC_DISTANCE + (n.getLocalBounds().width / 2)) {
                auto vec = GetRelativeVectorNormalized(*this, n.getPosition());
                if (GetDistance(vec, {0.f, 0.f}) > -AI_CRUISING_SPEED) {
                    speed -= vec * accelerationAverage;
                    continue;
                }
            }
            auto vec = GetRelativeVectorNormalized(*this, n.getPosition());
            if (GetDistance(vec, {0.f, 0.f}) > AI_SAFE_DISTANCE_SPEED) {
                speed -= vec * accelerationAverage;
                continue;
            }
        }
    }

    if (!isPanicking) {
        // moving towards player
        float distance = GetDistance(coords, ships.front().coords);
        //std::cout << distance << " is the distance\n";
        if (distance < AI_SAFE_DISTANCE + ships.front().collisionRadius) {
            if (distance < AI_PANIC_DISTANCE + ships.front().collisionRadius) {
                //std::cout << "PANIC!\n";
                auto vec = GetRelativeVectorNormalized(*this, ships.front().coords);
                if (GetDistance(vec, {0.f, 0.f}) > -AI_CRUISING_SPEED) {
                    speed -= vec * accelerationAverage;
                    //std::cout << "Change by: " << (vec * accelerationAverage).x << " " << (vec * accelerationAverage).y << "\n";
                }
            }
            else {
                //std::cout << "SAFE!\n";
                auto vec = GetRelativeVectorNormalized(*this, ships.front().coords);
                if (GetDistance(vec, {0.f, 0.f}) > AI_SAFE_DISTANCE_SPEED) {
                    speed -= vec * accelerationAverage * 2.f;
                    //std::cout << "Change by: " << (vec * accelerationAverage).x << " " << (vec * accelerationAverage).y << "\n";
                }
            }
        }
        else {
            //std::cout << "NORMAL!\n";
            if (distance > AI_SAFE_DISTANCE + ships.front().collisionRadius + 400.f) {
                auto vec = GetRelativeVectorNormalized(*this, ships.front().coords);
                speed += vec * accelerationAverage;
                //std::cout << "Change by: " << (vec * accelerationAverage).x << " " << (vec * accelerationAverage).y << "\n";
            }
        }
    }

    // avoiding other ships since this can happen
    for (unsigned int n = 1; n < ships.size(); n++) {
        if (ships[n].id != id) {
            float distance = GetDistance(coords, ships[n].coords);
            if (distance < AI_SAFE_DISTANCE + ships[n].collisionRadius) {
                if (distance < AI_PANIC_DISTANCE + ships[n].collisionRadius) {
                    auto vec = GetRelativeVectorNormalized(*this, ships[n].coords);
                    if (GetDistance(vec, {0.f, 0.f}) > -AI_CRUISING_SPEED) {
                        speed -= vec * accelerationAverage;
                    }
                }
                else {
                    auto vec = GetRelativeVectorNormalized(*this, ships[n].coords);
                    if (GetDistance(vec, {0.f, 0.f}) > AI_SAFE_DISTANCE_SPEED) {
                        speed -= vec * accelerationAverage;
                    }
                }
            }
        }
    }

    if (GetDistance(speed, {0.f, 0.f}) > AI_CRUISING_SPEED) {
        speed *= AI_CRUISING_SPEED / GetDistance(speed, {0.f, 0.f});
    }

    // shooting
    for (auto& n : weapons) {
        if (n.reloadLeft > 0) {
            n.reloadLeft--;
        }
        else if (std::abs(angle) < AI_STOP_ANGLE){
            // shoott
            sf::Vector2f offset = n.spritePointer->getOrigin() - sf::Vector2f(16.f, 16.f);
            float distance = GetDistance(offset, {0.f,0.f});
            float angle = std::asin(-offset.x / distance);
            if (offset.y < 0.f) {
                angle = 3.1415f - angle;
            }
            angle += rotation * 0.017452778f;
            offset.x = std::sin(angle) * distance;
            offset.y = -std::cos(angle) * distance;
            AddProjectile(offset + coords, rotation, n.partPointer, id);
            n.reloadLeft = n.partPointer->getReloadTime();
        }
    }


    coords = coords + (speed / 60.f);
    rotation = std::fmod(rotation + angularSpeed, 360.f);
    setRotation(rotation);
    setPosition(coords);
}

Ship::Ship(std::vector <EditorShipPart>& parts, sf::Vector2f position) {

    id = ids;
    ids++;

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
    accelerationAverage = (accelerationFront + accelerationRight + accelerationBack + accelerationLeft) / 12.f;
    accelerationRotation = float(power - drain) / float(power) / 1000.f;
    this->coords = position;
    if (width.x > width.y) {
        collisionRadius = width.x * 16.f;
    }
    else {
        collisionRadius = width.y * 16.f;
    }
    maxHealth = health;

    healthBar = HealthBar(collisionRadius + 64);

    //std::cout << "Created a ship with accelerations: " << accelerationFront << " " << accelerationRight << " " << accelerationBack << " " << accelerationLeft << "\n";
    //std::cout << "Mass: " << weight << "\n";
    //std::cout << "Power: " << power << "\n";
    //std::cout << "Drain: " << drain << "\n";
    //std::cout << "Health: " << health << "\n";
    //std::cout << "Rotation: " << accelerationRotation << "\n";
}

void Ship::draw(sf::RenderWindow& target) {
    while (shipDrawLock){
        sf::sleep(sf::microseconds(10));
    }
    shipDrawLock = true;
    for (auto& n : partSprites) {
        target.draw(n);
    }
    healthBar.draw(target, coords, ships.front().rotation, health, maxHealth);
    shipDrawLock = false;
}

void Ship::draw(sf::RenderTexture& target) {
    while (shipDrawLock){
        sf::sleep(sf::microseconds(10));
    }
    shipDrawLock = true;
    for (auto& n : partSprites) {
        target.draw(n);
    }
    healthBar.draw(target, coords, ships.front().rotation, health, maxHealth);
    shipDrawLock = false;
}

void Ship::setPosition(sf::Vector2f position) {
    while (shipDrawLock){
        sf::sleep(sf::microseconds(10));
    }
    shipDrawLock = true;
    for (auto& n : partSprites) {
        n.setPosition(position);
    }
    shipDrawLock = false;
}

void Ship::setRotation(float rotation) {
    while (shipDrawLock){
        sf::sleep(sf::microseconds(10));
    }
    shipDrawLock = true;
    for (auto& n : partSprites) {
        n.setRotation(rotation);
    }
    shipDrawLock = false;
}

void DealDamageToShip(int damage, unsigned int index) {
    std::cout << damage << " given to ship with health of " << ships[index].health << " / " << ships[index].maxHealth << "\n";

    ships[index].health -= damage;
    if (ships[index].health <= 0) {
        if (index == 0) {
            // game over!
            logicVector.clear();
            logicVector.emplace_back(LogicStage::gameOver, true);
            renderVector.clear();
            renderVector.push_back(Element::gameOver);
            return;
        }

        while (gameplayElementLock){
            sf::sleep(sf::microseconds(10));
        }
        gameplayElementLock = true;
        ships.erase(ships.begin() + index);
        gameplayElementLock = false;
    }
}