#include "collision.hpp"
#include "aux.hpp"

inline bool DoesCollideGeneral(const sf::Vector2f& first, const sf::Vector2f& second, float firstRadius, float secondRadius) {
    if (GetDistance(first, second) < firstRadius + secondRadius) {
        return true;
    }
    return false;
}

inline float GetThisElipseRadius(Ship& ship, float rotation) {
    return 0.f;
}

bool DoesCollide(sf::Sprite& first, Ship& second) {
    return false;
}

bool DoesCollide(Ship& first, Ship& second) {
    return false;
}

bool DoesCollide(Projectile& first, Ship& second) {
    return false;
}

bool DoesCollide(Projectile& first, sf::Sprite& second) {
    return DoesCollideGeneral(first.sprite.getPosition(), second.getPosition(), first.radius, second.getScale().x * 16);
}
