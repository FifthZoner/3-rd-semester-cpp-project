#include "healthBar.hpp"
#include "settings.hpp"

HealthBar::HealthBar(float distance) {
    //this->distance = distance;
    redBar.setFillColor(sf::Color::Red);
    redBar.setSize(sf::Vector2f(100.f, 16.f));
    redBar.setOrigin(redBar.getSize().x / 2, -distance);
    greenBar.setFillColor(sf::Color::Green);
    greenBar.setOrigin(redBar.getSize().x / 2, -distance);
}

void HealthBar::draw(sf::RenderWindow& target, sf::Vector2f& position, float& rotation, int& health, int& maxHealth) {
    redBar.setPosition(position);
    redBar.setRotation(rotation);
    target.draw(redBar);
    greenBar.setSize(sf::Vector2f(100.f * float(health) / float(maxHealth), 16.f));
    greenBar.setPosition(position);
    greenBar.setRotation(rotation);
    target.draw(greenBar);
}

void HealthBar::draw(sf::RenderTexture& target, sf::Vector2f& position, float& rotation, int& health, int& maxHealth) {
    redBar.setPosition(position);
    redBar.setRotation(rotation);
    target.draw(redBar);
    greenBar.setSize(sf::Vector2f(100.f * float(health) / float(maxHealth), 16.f));
    greenBar.setPosition(position);
    greenBar.setRotation(rotation);
    target.draw(greenBar);
}
