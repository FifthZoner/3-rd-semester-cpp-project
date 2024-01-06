#include <complex>
#include <iostream>
#include "collision.hpp"
#include "aux.hpp"
#include "gameplayHandling.hpp"

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

void HandleCollisions() {
    // ship to asteroid
    for (auto& n : ships) {
        for (auto& m : asteroids) {
            if (DoesCollide(m, n)) {
                // damage and bounce back
            }
        }
    }

    // ship to ship
    for (unsigned int n = 0; n < ships.size(); n++) {
        for (unsigned int m = n + 1; m < ships.size(); m++) {
            if (DoesCollide(ships[n], ships[m])) {
                // damage and bounce back
            }
        }
    }

    for (unsigned int n = 0; n < projectiles.size(); n++) {

        bool isDeleted = false;

        for (unsigned int m = 0; m < ships.size(); m++) {
            if (DoesCollide(projectiles[n], ships[m])) {
                // damage
                DealDamageToShip(projectiles[n].damage, m);

                while (gameplayProjectileLock){
                    sf::sleep(sf::microseconds(10));
                }
                gameplayProjectileLock = true;
                projectiles.erase(projectiles.begin() + n);
                gameplayProjectileLock = false;
                n--;
                isDeleted = true;
                break;
            }
        }

        if (isDeleted) {
            continue;
        }

        for (auto& m : asteroids) {
            if (DoesCollide(projectiles[n], m)) {
                while (gameplayProjectileLock){
                    sf::sleep(sf::microseconds(10));
                }
                gameplayProjectileLock = true;
                projectiles.erase(projectiles.begin() + n);
                gameplayProjectileLock = false;
                n--;
                break;
            }
        }
    }
}