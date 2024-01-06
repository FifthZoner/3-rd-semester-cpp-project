#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_HEALTHBAR_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_HEALTHBAR_HPP

#include <SFML/Graphics.hpp>

struct HealthBar {
    sf::RectangleShape redBar, greenBar;
    //float distance = 0.f;

    HealthBar() = default;
    HealthBar(float distance);

    void draw(sf::RenderWindow& target, sf::Vector2f& position, float& rotation, int& health, int& maxHealth);
    void draw(sf::RenderTexture& target, sf::Vector2f& position, float& rotation, int& health, int& maxHealth);
};

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_HEALTHBAR_HPP
