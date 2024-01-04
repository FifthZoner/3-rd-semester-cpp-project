#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_GAMEPLAYHANDLING_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_GAMEPLAYHANDLING_HPP

#include <array>
#include "SFML/Graphics/Sprite.hpp"

inline volatile bool gameplayElementLock = false;
inline volatile bool gameplayProjectileLock = false;

void HandleGameplay();

#define ASTEROID_COUNT 20

inline std::array <sf::Sprite, ASTEROID_COUNT> asteroids;

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_GAMEPLAYHANDLING_HPP
