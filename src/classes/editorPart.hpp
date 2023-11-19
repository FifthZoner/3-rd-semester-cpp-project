#ifndef EDITOR_PART_HPP
#define EDITOR_PART_HPP

#include "part.hpp"
#include <SFML/Graphics.hpp>

struct EditorPart {
    ShipPart* pointer;
    sf::Sprite part;
    sf::Sprite points[4];
};

#endif