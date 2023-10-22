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
    texturePath = "";
    textureRect = nullptr;
}

Texturable::~Texturable(){ 
}