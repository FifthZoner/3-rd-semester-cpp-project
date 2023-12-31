#include "part.hpp"
#include "../misc/misc.hpp"
#include "../misc/texturePacker.hpp"

void MountPoints::setPoint(uint8_t side, uint8_t point){
    switch (side){
        case front:
            frontPoint = point;
            break;
        case right:
            rightPoint = point;
            break;
        case back:
            backPoint = point;
            break;
        case left:
            leftPoint = point;
            break;
        default:
            break;
    }
 }

uint8_t MountPoints::getPoint(uint8_t side){
    switch (side){
        case front:
            return frontPoint;
            break;
        case right:
            return rightPoint;
            break;
        case back:
            return backPoint;
            break;
        case left:
            return leftPoint;
            break;
        default:
            return 0;
            break;
    }
}

MountPoints::MountPoints(){
    frontPoint = none;
    rightPoint = none;
    backPoint = none;
    leftPoint = none;
}

MountPoints::MountPoints(uint8_t front, uint8_t right, uint8_t back, uint8_t left){
    frontPoint = front;
    rightPoint = right;
    backPoint = back;
    leftPoint = left;
}

MountPoints::~MountPoints(){}

uint8_t StrToPoint(std::string& string){
    if (string == "present"){
        return MountPoints::Type::present;
    }
    if (string == "none"){
        return MountPoints::Type::none;
    }
    if (string == "restricted"){
        return MountPoints::Type::restricted;
    }
    return MountPoints::Type::error;
}

void ShipPart::create(std::string path){
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

std::string ShipPart::getName(){
    return name;
}
std::string ShipPart::getDesc(){
    return description;
}
uint32_t ShipPart::getWeight(){
    return weight;
}
uint32_t ShipPart::getHealth(){
    return health;
}

ShipPart::ShipPart(){
    name = "N/A";
    description = "N/A";
    textureRect = nullptr;
    weight = 0;
    health = 0;
}

ShipPart::ShipPart(std::string path){
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

ShipPart::~ShipPart(){}

const sf::IntRect* ShipPart::getRectPointer() const{
    return textureRect;
}

const MountPoints& ShipPart::getMountPoints() const {
    return mountPoints;
}

uint8_t ShipPart::type() {
    return PartType::structural;
}