#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_WEAPON_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_WEAPON_HPP

#include "../part.hpp"

class ShipWeapon : public ShipPart {
private:
    uint16_t drain = 0;
    float projectileSpread = 0.f;
public:
    [[nodiscard]] uint16_t getDrain() const;

    [[nodiscard]] float getProjectileSpread() const;

    [[nodiscard]] float getProjectileScale() const;

    [[nodiscard]] float getProjectileSpeed() const;

    [[nodiscard]] float getProjectileWidth() const;

    [[nodiscard]] unsigned int getProjectileDamage() const;

    [[nodiscard]] unsigned int getReloadTime() const;

    [[nodiscard]] Texturable &getProjectile();

private:
    float projectileScale = 1.f;
    float projectileSpeed = 0.f;
    float projectileWidth = 1.f;
    unsigned int projectileDamage = 0;
    unsigned int reloadTime = 0;
    Texturable projectile;
public:
    uint16_t getPower() const;

public:
    void create(std::string path) override;
    ShipWeapon(std::string path);
    uint8_t type() override;
};

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_WEAPON_HPP
