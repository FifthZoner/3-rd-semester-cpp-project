#ifndef SLIDER_BUTTON_HPP
#define SLIDER_BUTTON_HPP

#include "button.hpp"

// A slider button for sliding!
// can be moved around in every direction!
// The position is at the center of the button due to it's goal, might be changed
class SliderButton : public Button {
protected:

    sf::Rect <float> allowed;

public:

    void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, sf::Color borderColor,
        uint8_t borderWidth, sf::Color clickedBackgroundColor, sf::Rect <float> allowedRange);

    void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
        sf::Color borderColor, uint8_t borderWidth, sf::Color clickedBackgroundColor, 
        sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize, sf::Rect <float> allowedRange);

    // pass mouse position relative to the window
    // also updates the object, this might get moved into rendering for better fluidity but might not be required
    sf::Vector2i getPosition(sf::Vector2i position);

    sf::Vector2f getPart(sf::Vector2i position);

    sf::Vector2f getOffset();

    SliderButton();

    ~SliderButton();
};

#endif