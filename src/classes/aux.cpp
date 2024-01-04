#include "aux.hpp"

#include <cmath>

float GetDistance(sf::Vector2f first, sf::Vector2f second) {
    return std::sqrt(std::pow(first.x - second.x, 2.f) + std::pow(first.y - second.y, 2.f));
}