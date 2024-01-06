#include <cmath>
#include <iostream>
#include "projectile.hpp"
#include "aux.hpp"
#include "gameplayHandling.hpp"

#define MAX_PROJECTILE_DISTANCE 5000.f

Projectile::Projectile(sf::Vector2f position, float rotation, ShipWeapon* origin) {
    origin->getProjectile().setSprite(sprite);
    speed = sf::Vector2f(origin->getProjectileSpeed() * std::sin(rotation * 0.017452778f), -origin->getProjectileSpeed() * std::cos(rotation * 0.017452778f)) / 60.f;
    sprite.setScale(origin->getProjectileScale(), origin->getProjectileScale());
    sprite.setOrigin(16.f * origin->getProjectileScale(), 16.f * origin->getProjectileScale());
    sprite.setPosition(position);
    sprite.setRotation(rotation);
    startingPoint = position;
    radius = origin->getProjectileWidth() / 2;
    damage = origin->getProjectileDamage();
}

// returns true if it needs to be deleted
bool Projectile::handleTick() {

    sprite.move(speed);

    if (GetDistance(sprite.getPosition(), startingPoint) > MAX_PROJECTILE_DISTANCE) {
        return true;
    }

    // add collision here

    return false;
}

void AddProjectile(sf::Vector2f position, float rotation, ShipWeapon* origin) {
    while (gameplayProjectileLock){
        sf::sleep(sf::microseconds(10));
    }
    gameplayProjectileLock = true;

    projectiles.emplace_back(position, rotation, origin);

    gameplayProjectileLock = false;
}

void HandleProjectiles() {
    for (unsigned int n = 0; n < projectiles.size(); n++) {
        if (projectiles[n].handleTick()) {
            // deleting
            while (gameplayProjectileLock){
                sf::sleep(sf::microseconds(10));
            }
            gameplayProjectileLock = true;
            projectiles.erase(projectiles.begin() + n);
            gameplayProjectileLock = false;
            n--;
        }
    }
}