#include "aux.hpp"

#include <cmath>
#include <iostream>

float GetDistance(sf::Vector2f first, sf::Vector2f second) {
    return std::sqrt(std::pow(first.x - second.x, 2.f) + std::pow(first.y - second.y, 2.f));
}

float GetRotationRelativeRadians(sf::Vector2f reference, sf::Vector2f target) {
    reference = target - reference;
    float angle = std::asin(reference.x / std::sqrt(reference.x * reference.x + reference.y * reference.y));
    if (reference.y > 0.f) {
        angle = 3.1415f - angle;
    }
    return angle;
}
float GetRotationRelativeDegrees(sf::Vector2f reference, sf::Vector2f target) {
    reference = target - reference;
    float angle = std::asin(reference.x / std::sqrt(reference.x * reference.x + reference.y * reference.y));
    if (reference.y > 0.f) {
        angle = 3.1415f - angle;
    }
    return angle * 57.297469362f;
}

sf::Vector2f GetRelativeVector(Ship& reference, sf::Vector2f target) {
    sf::Vector2f i = target - reference.coords;
    float betaPlusGamma = std::asin(i.x / std::sqrt(i.x * i.x + i.y * i.y));
    if (i.y > 0.f) {
        betaPlusGamma = 3.1415f - betaPlusGamma;
    }

    float beta;
    if (reference.speed.x > 0 or reference.speed.y > 0) {
        beta = std::asin(reference.speed.x / std::sqrt(reference.speed.x * reference.speed.x + reference.speed.y * reference.speed.y));
    }
    else {
        beta = 0;
    }

    if (reference.speed.y > 0.f) {
        beta = 3.1415f - beta;
    }

    float impactSpeed = std::cos(betaPlusGamma - beta) * GetDistance(sf::Vector2f(0, 0), reference.speed);
    return {std::sin(betaPlusGamma) * impactSpeed, -std::cos(betaPlusGamma) * impactSpeed};
}
sf::Vector2f GetRelativeVectorNormalized(Ship& reference, sf::Vector2f target) {
    sf::Vector2f normalized = target - reference.coords;
    return normalized * GetDistance(normalized, {0.f, 0.f});

    sf::Vector2f i = target - reference.coords;
    float betaPlusGamma = std::asin(i.x / std::sqrt(i.x * i.x + i.y * i.y));
    if (i.y > 0.f) {
        betaPlusGamma = 3.1415f - betaPlusGamma;
    }

    float beta;
    if (reference.speed.x > 0 or reference.speed.y > 0) {
        beta = std::asin(reference.speed.x / std::sqrt(reference.speed.x * reference.speed.x + reference.speed.y * reference.speed.y));
    }
    else {
        beta = 0;
    }

    if (reference.speed.y > 0.f) {
        beta = 3.1415f - beta;
    }

    float impactSpeed = std::cos(betaPlusGamma - beta);
    return {std::sin(betaPlusGamma) * impactSpeed, -std::cos(betaPlusGamma) * impactSpeed};
}
float GetRelativeSpeed(Ship& reference, sf::Vector2f target) {
    sf::Vector2f i = target - reference.coords;
    float betaPlusGamma = std::asin(i.x / std::sqrt(i.x * i.x + i.y * i.y));
    if (i.y > 0.f) {
        betaPlusGamma = 3.1415f - betaPlusGamma;
    }

    float beta;
    if (reference.speed.x > 0 or reference.speed.y > 0) {
        beta = std::asin(reference.speed.x / std::sqrt(reference.speed.x * reference.speed.x + reference.speed.y * reference.speed.y));
    }
    else {
        beta = 0;
    }
    if (reference.speed.y > 0.f) {
        beta = 3.1415f - beta;
    }

    return std::cos(betaPlusGamma - beta) * GetDistance(sf::Vector2f(0, 0), reference.speed);
}