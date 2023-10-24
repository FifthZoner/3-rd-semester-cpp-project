#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "frame.hpp"

class Button : public Frame{
protected:

    bool isClicked;
    sf::Color clickedColor;
    sf::Color idleColor;

public:

    // this function changes the color, returns the bool AND handles the effect function
    bool checkClick(const sf::Vector2i& position);

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, sf::Color borderColor,
    uint8_t borderWidth, sf::Color clickedBackgroundColor);

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
    sf::Color borderColor, uint8_t borderWidth, sf::Color clickedBackgroundColor, 
    sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize);

    void draw(sf::RenderWindow& window);

    Button();

    ~Button();

};

#endif