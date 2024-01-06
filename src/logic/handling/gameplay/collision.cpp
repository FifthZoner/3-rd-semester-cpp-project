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
    for (unsigned int n = 0; n < ships.size(); n++) {
        for (auto& m : asteroids) {
            if (DoesCollide(m, ships[n])) {
                sf::Vector2f i = m.getPosition() - ships[n].coords;
                float betaPlusGamma = std::asin(i.x / std::sqrt(i.x * i.x + i.y * i.y));
                if (i.y > 0.f) {
                    betaPlusGamma = 3.1415f - betaPlusGamma;
                }

                float beta = std::asin(ships[n].speed.x / std::sqrt(ships[n].speed.x * ships[n].speed.x + ships[n].speed.y * ships[n].speed.y));
                if (ships[n].speed.y > 0.f) {
                    beta = 3.1415f - beta;
                }

                float impactSpeed = std::cos(betaPlusGamma - beta) * GetDistance(sf::Vector2f(0, 0), ships[n].speed);
                sf::Vector2f impactVector = {std::sin(betaPlusGamma) * impactSpeed, -std::cos(betaPlusGamma) * impactSpeed};
                ships[n].speed -= impactVector * 1.5f;
                ships[n].coords = ships[n].coords - (sf::Vector2f(std::sin(betaPlusGamma), -std::cos(betaPlusGamma)) * 5.f);
                ships[n].setPosition(ships[n].coords);

                DealDamageToShip(int(std::floor(impactSpeed / 50.f)), n);
            }
        }
    }

    // ship to ship
    for (unsigned int n = 0; n < ships.size(); n++) {
        for (unsigned int m = n + 1; m < ships.size(); m++) {
            if (DoesCollide(ships[n], ships[m])) {
                // damage and bounce back

                int damage = 0;

                // first ship
                if (ships[n].speed != sf::Vector2f(0, 0)) {
                    sf::Vector2f i = ships[m].coords - ships[n].coords;
                    float betaPlusGamma = std::asin(i.x / std::sqrt(i.x * i.x + i.y * i.y));
                    if (i.y > 0.f) {
                        betaPlusGamma = 3.1415f - betaPlusGamma;
                    }

                    float beta = std::asin(ships[n].speed.x / std::sqrt(ships[n].speed.x * ships[n].speed.x + ships[n].speed.y * ships[n].speed.y));
                    if (ships[n].speed.y > 0.f) {
                        beta = 3.1415f - beta;
                    }

                    float impactSpeed = std::cos(betaPlusGamma - beta) * GetDistance(sf::Vector2f(0, 0), ships[n].speed);
                    sf::Vector2f impactVector = {std::sin(betaPlusGamma) * impactSpeed, -std::cos(betaPlusGamma) * impactSpeed};
                    ships[n].speed -= impactVector * 1.5f;
                    ships[n].coords = ships[n].coords - (sf::Vector2f(std::sin(betaPlusGamma), -std::cos(betaPlusGamma)) * 5.f);
                    ships[n].setPosition(ships[n].coords);

                    DealDamageToShip(int(std::floor(impactSpeed / 50.f)), n);

                    damage += int(std::floor(impactSpeed / 50.f));
                }

                // second ship
                if (ships[m].speed != sf::Vector2f(0, 0)) {
                    sf::Vector2f i = ships[n].coords - ships[m].coords;
                    float betaPlusGamma = std::asin(i.x / std::sqrt(i.x * i.x + i.y * i.y));
                    if (i.y > 0.f) {
                        betaPlusGamma = 3.1415f - betaPlusGamma;
                    }

                    float beta = std::asin(ships[m].speed.x / std::sqrt(ships[m].speed.x * ships[m].speed.x + ships[m].speed.y * ships[m].speed.y));
                    if (ships[m].speed.y > 0.f) {
                        beta = 3.1415f - beta;
                    }

                    float impactSpeed = std::cos(betaPlusGamma - beta) * GetDistance(sf::Vector2f(0, 0), ships[m].speed);
                    sf::Vector2f impactVector = {std::sin(betaPlusGamma) * impactSpeed, -std::cos(betaPlusGamma) * impactSpeed};
                    ships[m].speed -= impactVector * 1.5f;
                    ships[m].coords = ships[m].coords - (sf::Vector2f(std::sin(betaPlusGamma), -std::cos(betaPlusGamma)) * 5.f);
                    ships[m].setPosition(ships[m].coords);

                    damage += int(std::floor(impactSpeed / 50.f));
                }
                DealDamageToShip(damage, m);
                DealDamageToShip(damage, n);
            }
        }
    }

    for (unsigned int n = 0; n < projectiles.size(); n++) {

        bool isDeleted = false;

        for (unsigned int m = 0; m < ships.size(); m++) {
            if (ships[m].id != projectiles[n].origin and DoesCollide(projectiles[n], ships[m])) {
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