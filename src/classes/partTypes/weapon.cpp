#include "weapon.hpp"
#include "misc.hpp"

void ShipWeapon::create(std::string path) {
    auto content = std::move(ParseTextFile(std::move(path)));

    // just to be safe in case of errors
    name = "N/A";
    description = "N/A";
    textureRect = new sf::IntRect();
    weight = 0;
    health = 0;
    std::string texturePath = "N/A";

    for (auto next : content){
        if (next.size() == 2){
            if (next[0] == "name"){
                name = next[1];
            }
            else if (next[0] == "description"){
                description = next[1];
            }
            else if (next[0] == "texture"){
                texturePath = next[1];
            }
            else if (next[0] == "health"){
                health = stoi(next[1]);
            }
            else if (next[0] == "weight"){
                weight = stoi(next[1]);
            }
            else if (next[0] == "drain"){
                drain = stoi(next[1]);
            }
            else if (next[0] == "damage"){
                projectileDamage = stoi(next[1]);
            }
            else if (next[0] == "reload"){
                reloadTime = stoi(next[1]);
            }
            else if (next[0] == "spread"){
                projectileSpread = stof(next[1]);
            }
            else if (next[0] == "scale"){
                projectileScale = stof(next[1]);
            }
            else if (next[0] == "speed"){
                projectileSpeed = stof(next[1]);
            }
            else if (next[0] == "width"){
                projectileWidth = stof(next[1]);
            }
            else if (next[0] == "projectile"){
                projectile.loadTextureStandalone(next[1]);
            }
            else if (next[0] == "front"){
                mountPoints.setPoint(MountPoints::Point::front, StrToPoint(next[1]));
            }
            else if (next[0] == "right"){
                mountPoints.setPoint(MountPoints::Point::right, StrToPoint(next[1]));
            }
            else if (next[0] == "back"){
                mountPoints.setPoint(MountPoints::Point::back, StrToPoint(next[1]));
            }
            else if (next[0] == "left"){
                mountPoints.setPoint(MountPoints::Point::left, StrToPoint(next[1]));
            }
        }
    }

    AddTextureToPack(texturePath, textureRect);
}

ShipWeapon::ShipWeapon(std::string path) {
    auto content = std::move(ParseTextFile(std::move(path)));

    // just to be safe in case of errors
    name = "N/A";
    description = "N/A";
    textureRect = new sf::IntRect();
    weight = 0;
    health = 0;
    std::string texturePath = "N/A";

    for (auto next : content){
        if (next.size() == 2){
            if (next[0] == "name"){
                name = next[1];
            }
            else if (next[0] == "description"){
                description = next[1];
            }
            else if (next[0] == "texture"){
                texturePath = next[1];
            }
            else if (next[0] == "health"){
                health = stoi(next[1]);
            }
            else if (next[0] == "weight"){
                weight = stoi(next[1]);
            }
            else if (next[0] == "drain"){
                drain = stoi(next[1]);
            }
            else if (next[0] == "damage"){
                projectileDamage = stoi(next[1]);
            }
            else if (next[0] == "reload"){
                reloadTime = stoi(next[1]);
            }
            else if (next[0] == "spread"){
                projectileSpread = stof(next[1]);
            }
            else if (next[0] == "scale"){
                projectileScale = stof(next[1]);
            }
            else if (next[0] == "speed"){
                projectileSpeed = stof(next[1]);
            }
            else if (next[0] == "width"){
                projectileWidth = stof(next[1]);
            }
            else if (next[0] == "projectile"){
                projectile.loadTextureStandalone(next[1]);
            }
            else if (next[0] == "front"){
                mountPoints.setPoint(MountPoints::Point::front, StrToPoint(next[1]));
            }
            else if (next[0] == "right"){
                mountPoints.setPoint(MountPoints::Point::right, StrToPoint(next[1]));
            }
            else if (next[0] == "back"){
                mountPoints.setPoint(MountPoints::Point::back, StrToPoint(next[1]));
            }
            else if (next[0] == "left"){
                mountPoints.setPoint(MountPoints::Point::left, StrToPoint(next[1]));
            }
        }
    }

    AddTextureToPack(texturePath, textureRect);
}

uint8_t ShipWeapon::type() {
    return PartType::weapon;
}

uint16_t ShipWeapon::getDrain() const {
    return drain;
}

float ShipWeapon::getProjectileSpread() const {
    return projectileSpread;
}

float ShipWeapon::getProjectileScale() const {
    return projectileScale;
}

float ShipWeapon::getProjectileSpeed() const {
    return projectileSpeed;
}

float ShipWeapon::getProjectileWidth() const {
    return projectileWidth;
}

unsigned int ShipWeapon::getProjectileDamage() const {
    return projectileDamage;
}

unsigned int ShipWeapon::getReloadTime() const {
    return reloadTime;
}

Texturable &ShipWeapon::getProjectile() {
    return projectile;
}
