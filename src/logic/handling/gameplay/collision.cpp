#include <complex>
#include <iostream>
#include "collision.hpp"
#include "aux.hpp"

inline bool DoesCollideGeneral(const sf::Vector2f& first, const sf::Vector2f& second, float firstRadius, float secondRadius) {
    if (GetDistance(first, second) < firstRadius + secondRadius) {
        return true;
    }
    return false;
}

bool DoesCollide(sf::Sprite& first, Ship& second) {
    return DoesCollideGeneral(first.getPosition(), second.coords, first.getScale().x * 16, second.collisionRadius);
}

bool DoesCollide(Ship& first, Ship& second) {
    return DoesCollideGeneral(first.coords, second.coords, first.collisionRadius, second.collisionRadius);
}

bool DoesCollide(Projectile& first, Ship& second) {
    return DoesCollideGeneral(first.sprite.getPosition(), second.coords, first.radius, second.collisionRadius);
}

bool DoesCollide(Projectile& first, sf::Sprite& second) {
    return DoesCollideGeneral(first.sprite.getPosition(), second.getPosition(), first.radius, second.getScale().x * 16);
}
