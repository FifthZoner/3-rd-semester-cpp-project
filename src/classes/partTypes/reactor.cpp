#include "reactor.hpp"
#include "misc.hpp"


void ShipReactor::create(std::string path) {
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
            else if (next[0] == "power"){
                power = stoi(next[1]);
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

ShipReactor::ShipReactor(std::string path) {
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
            else if (next[0] == "power"){
                power = stoi(next[1]);
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