#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

// empty
struct ButtonContent {

    virtual void draw(sf::RenderWindow& window);

    ButtonContent();
};

struct ButtonText : public ButtonContent {

    sf::Text text;

    void draw(sf::RenderWindow& window);

    // for now no alignment options, pass the position in the middle of the button
    ButtonText(sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize, sf::Vector2f position);
};

// not to be implemented as of now
struct ButtonImage : public ButtonContent {

    void draw(sf::RenderWindow& window);

    ButtonImage();
};

class Button {
private:

    sf::ConvexShape frame;

    void (*runFunction)();

    ButtonContent* content;

    sf::Color clickedColor;
    sf::Color idleColor;

    bool isClicked;

public:

    // this function changes the color, returns the bool AND handles the effect function
    bool checkClick(sf::Vector2f position);

    void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, sf::Color borderColor,
    void (*function)(), uint8_t borderWidth, sf::Color clickedBackgroundColor);

    void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
    sf::Color borderColor, void (*function)(), uint8_t borderWidth, sf::Color clickedBackgroundColor, 
    sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize);

    void draw(sf::RenderWindow& window);

    Button();

    ~Button();

};

#endif