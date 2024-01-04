#include "projectile.hpp"

Projectile::Projectile(sf::Vector2f position, float rotation, ShipWeapon* origin) {
    origin->getProjectile().setSprite(sprite);
    sprite.setScale(origin->getProjectileScale(), origin->getProjectileScale());
    sprite.setOrigin(16.f * origin->getProjectileScale(), 16.f * origin->getProjectileScale());
    sprite.setPosition(position);
    sprite.setRotation(rotation);
}

// returns true if it needs to be deleted
bool Projectile::handleTick() {





    return false;
}