#ifndef TEXTURE_PACKER_HPP
#define TEXTURE_PACKER_HPP

#include <string>
#include <SFML/Graphics/Rect.hpp>

struct PackerStruct {

    std::string path;
    sf::IntRect* rect;
    sf::Texture texture;
    sf::Sprite sprite;

    PackerStruct(std::string path, sf::IntRect* rect);

};

// you MUST manually push to the "extern std::vector <Texturable*> affectedTexturables" after that if you want the texture to update after packing
// not needed required for parts as the textures are set later other way
void AddTextureToPack(const std::string& path, sf::IntRect* rect);

void RunTexturePacking();

const sf::Texture& GetMainTexture();

#endif