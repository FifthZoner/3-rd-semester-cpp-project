#ifndef PART_HPP
#define PART_HPP

#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

struct MountPoints{
    uint8_t front:2 = none;
    uint8_t left:2 = none;
    uint8_t right:2 = none;
    uint8_t back:2 = none;

    // none - no connection
    // present - can be connected in any way
    // restricted - cannot have anything placed there due to it's output
    enum type{
        none, present, restricted
    };
};

class ShipPart {
protected:
    MountPoints mountPoints;
    std::string name;

public:

    virtual void draw(sf::RenderWindow& window);

    ShipPart();

    ~ShipPart();

};

#endif