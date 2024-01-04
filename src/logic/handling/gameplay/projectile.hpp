#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_PROJECTILE_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_PROJECTILE_HPP

#include "texturable.hpp"
#include "weapon.hpp"

struct Projectile {
    Texturable* projectilePointer;
    sf::Sprite sprite;
    sf::Vector2f startingPoint = {0.f, 0.f};
    sf::Vector2f speed = {0.f, 0.f};

    Projectile(sf::Vector2f position, float rotation, ShipWeapon* origin);
    // returns true if it needs to be deleted
    bool handleTick();
};

inline std::vector <Projectile> projectiles;

void AddProjectile(sf::Vector2f position, float rotation, ShipWeapon* origin);
void HandleProjectiles();

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_PROJECTILE_HPP
