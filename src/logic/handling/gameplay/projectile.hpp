#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_PROJECTILE_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_PROJECTILE_HPP

#include "texturable.hpp"
#include "weapon.hpp"

struct Projectile {
    Texturable* projectilePointer;
    sf::Sprite sprite;

    Projectile(sf::Vector2f position, float rotation, ShipWeapon* origin);
    // returns true if it needs to be deleted
    bool handleTick();
};

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_PROJECTILE_HPP
