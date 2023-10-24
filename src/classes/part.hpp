#ifndef PART_HPP
#define PART_HPP

#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

#include "gameData.hpp"
#include "../graphics/classes/simple/texturable.hpp"

class MountPoints{
private:
    uint8_t frontPoint:2;
    uint8_t leftPoint:2;
    uint8_t rightPoint:2;
    uint8_t backPoint:2;

public:

    enum Point{
        front, right, back, left
    };

    // none - no connection
    // present - can be connected in any way
    // restricted - cannot have anything placed there due to it's output
    enum Type{
        none, present, restricted, error
    };

    // pass the side as a number with 0 as front clockwise, if adding do a modulo
    void setPoint(uint8_t side, uint8_t point);

   // pass the side as a number with 0 as front clockwise, if adding do a modulo
   uint8_t getPoint(uint8_t side);

   MountPoints();

   MountPoints(uint8_t front, uint8_t right, uint8_t back, uint8_t left);

   ~MountPoints();
};

// this class defines a part, can be used for structural parts
class ShipPart : public Texturable {
protected:
    MountPoints mountPoints;
    std::string name, description;
    uint32_t weight, health;

public:

    // creates a part from definition
    virtual void create(std::string path);

    const sf::IntRect* getRectPointer() const;

    ShipPart();

    ShipPart(std::string path);

    ~ShipPart();

};

#endif