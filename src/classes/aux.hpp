#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_AUX_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_AUX_HPP

#include "SFML/System/Vector2.hpp"
#include "ship.hpp"

float GetDistance(sf::Vector2f first, sf::Vector2f second);

float GetRotationRelativeRadians(sf::Vector2f reference, sf::Vector2f target);
float GetRotationRelativeDegrees(sf::Vector2f reference, sf::Vector2f target);

sf::Vector2f GetRelativeVector(Ship& reference, sf::Vector2f target);
sf::Vector2f GetRelativeVectorNormalized(Ship& reference, sf::Vector2f target);
float GetRelativeSpeed(Ship& reference, sf::Vector2f target);

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_AUX_HPP
