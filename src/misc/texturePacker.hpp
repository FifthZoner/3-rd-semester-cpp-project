#ifndef TEXTURE_PACKER_HPP
#define TEXTURE_PACKER_HPP

#include <string>
#include <SFML/Graphics/Rect.hpp>

void AddTextureToPack(std::string path, sf::IntRect* rect);

void RunTexturePacking();

const sf::Texture& GetMainTexture();

#endif