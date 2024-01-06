#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_COLLISION_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_COLLISION_HPP

#include "SFML/Graphics/Sprite.hpp"
#include "ship.hpp"
#include "projectile.hpp"

bool DoesCollide(sf::Sprite& first, Ship& second);
bool DoesCollide(Ship& first, Ship& second);
bool DoesCollide(Projectile& first, Ship& second);
bool DoesCollide(Projectile& first, sf::Sprite& second);

void HandleCollisions();

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_COLLISION_HPP
