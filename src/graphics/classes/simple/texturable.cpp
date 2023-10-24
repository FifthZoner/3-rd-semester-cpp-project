#include <vector>

#include "texturable.hpp"

extern std::vector <Texturable*> affectedTexturables;

void Texturable::copyRect(Texturable* target){
    target->textureRect = textureRect;
    affectedTexturables.push_back(target);
}

void Texturable::setTexture(){
    // nothing to do here
}

Texturable::Texturable(){
    textureRect = nullptr;
}

Texturable::~Texturable(){ 
}

void Texturable::loadTextureStandalone(const std::string& path){
    textureRect = new sf::IntRect;
    AddTextureToPack(path, textureRect);
    affectedTexturables.push_back(this);
}