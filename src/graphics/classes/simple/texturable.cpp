#include <vector>

#include "texturable.hpp"

extern std::vector <Texturable*> affectedTexturables;

void Texturable::copyRectConfig(Texturable* target){
    target->textureRect = textureRect;
    affectedTexturables.push_back(target);
}

void Texturable::copyRect(Texturable* target){
    target->textureRect = textureRect;
    target->setTexture();
}

void Texturable::setTexture(){
    // nothing to do here
}

Texturable::Texturable(){
    textureRect = nullptr;
}

Texturable::~Texturable(){ 
}

void Texturable::setSprite(sf::Sprite& sprite, uint8_t rotation){
    sprite.setTexture(GetMainTexture());
    switch (rotation) {
        case 0:
            sprite.setTextureRect(*textureRect);
            break;
        case 1:
            sprite.setTextureRect(sf::IntRect(textureRect->getPosition() + sf::Vector2i(32, 0), textureRect->getSize()));
            break;
        case 2:
            sprite.setTextureRect(sf::IntRect(textureRect->getPosition() + sf::Vector2i(32, 32), textureRect->getSize()));
            break;
        case 3:
            sprite.setTextureRect(sf::IntRect(textureRect->getPosition() + sf::Vector2i(0, 32), textureRect->getSize()));
            break;
        default:
            sprite.setTextureRect(*textureRect);
            break;
    }
}

void Texturable::loadTextureStandalone(const std::string& path){
    textureRect = new sf::IntRect;
    AddTextureToPack(path, textureRect);
    affectedTexturables.push_back(this);
}