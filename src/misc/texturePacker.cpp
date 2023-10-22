#include <vector>
#include <SFML/Graphics.hpp>

#include "texturePacker.hpp"
#include "../graphics/classes/simple/texturable.hpp"


sf::RenderTexture mainTexture;

PackerStruct::PackerStruct(std::string path, sf::IntRect* rect){
        this->rect = rect;
        this->path = path;
}

std::vector <PackerStruct> packingList;
std::vector <Texturable> affectedTexturables;

void AddTextureToPack(std::string path, sf::IntRect* rect){
    packingList.push_back(PackerStruct(path, rect));
}

void SetTextures(){
    for (auto& index : affectedTexturables){
        index.setTexture();
    }
}

#include <iostream>

void RunTexturePacking(){

    // Figuring out texture size for given amount of elements
    // Assumes 32x32 images, I'll try to improve it in the future
    uint8_t side = 1;
    while (side*side < packingList.size()){
        side++;
    }

    std::cout << "Packer running with amount: " << packingList.size() << ", size: " << side * 1 << "\n";

    mainTexture.create(side * 32, side * 32);
    mainTexture.clear(sf::Color(0, 0, 0, 0));

    for (uint32_t n = 0; n < packingList.size(); n++){
        if (packingList[n].texture.loadFromFile(packingList[n].path)){
            packingList[n].sprite.setTexture(packingList[n].texture);
            packingList[n].sprite.setPosition(32 * (n % side), 32 * (n / side));
            mainTexture.draw(packingList[n].sprite);
            packingList[n].path.clear();
        }
        *packingList[n].rect = sf::IntRect(32 * (n % side), 32 * (n / 4), 32, 32);
    }

    mainTexture.display();

    SetTextures();

    packingList.clear();
    affectedTexturables.clear();
}

const sf::Texture& GetMainTexture(){
    return mainTexture.getTexture();
}