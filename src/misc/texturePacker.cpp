#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "texturePacker.hpp"
#include "../graphics/classes/simple/texturable.hpp"


sf::RenderTexture mainTexture;

PackerStruct::PackerStruct(std::string path, sf::IntRect* rect){
        this->rect = rect;
        this->path = path;
}

std::vector <PackerStruct> packingList;
std::vector <Texturable*> affectedTexturables;

void AddTextureToPack(const std::string& path, sf::IntRect* rect){
    packingList.emplace_back(path, rect);
}

void SetTextures(){
    for (auto index : affectedTexturables){
        index->setTexture();
    }
}

void RunTexturePacking(){

    // Figuring out texture size for given amount of elements
    // Assumes 32x32 images, I'll try to improve it in the future
    unsigned int side = 1;
    while (side*side < packingList.size()){
        side++;
    }

    mainTexture.create(side * 64, side * 64);
    mainTexture.clear(sf::Color(0, 0, 0, 0));
    for (uint32_t n = 0; n < packingList.size(); n++){
        if (packingList[n].texture.loadFromFile(packingList[n].path)){
            packingList[n].sprite.setTexture(packingList[n].texture);
            packingList[n].sprite.setPosition(64 * (n % side), 64 * floor(n / side));
            mainTexture.draw(packingList[n].sprite);
            packingList[n].sprite.rotate(90);
            packingList[n].sprite.move(64, 0);
            mainTexture.draw(packingList[n].sprite);
            packingList[n].sprite.rotate(90);
            packingList[n].sprite.move(0, 64);
            mainTexture.draw(packingList[n].sprite);
            packingList[n].sprite.rotate(90);
            packingList[n].sprite.move(-64, 0);
            mainTexture.draw(packingList[n].sprite);
            packingList[n].sprite.rotate(90);
            packingList[n].sprite.move(0, -64);
            packingList[n].path.clear();
        }
        *packingList[n].rect = sf::IntRect(64 * (n % side), 64 * floor(n / side), 32, 32);
    }

    mainTexture.display();
    SetTextures();

    packingList.clear();
    affectedTexturables.clear();
}

const sf::Texture& GetMainTexture(){
    return mainTexture.getTexture();
}