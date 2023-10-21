#ifndef FRAME_HPP
#define FRAME_HPP

#include <SFML/Graphics.hpp>

// empty
struct Content {

    virtual void draw(sf::RenderWindow& window);

    virtual void setPosition(float x, float y);

    Content();
};

struct ContentText : public Content {

    sf::Text text;

    void draw(sf::RenderWindow& window);

    // for now no alignment options, pass the position in the middle of the button
    ContentText(sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize, sf::Vector2f position);

    void setPosition(float x, float y);
};

// not to be implemented as of now
struct ContentImage : public Content {

    void draw(sf::RenderWindow& window);

    ContentImage();

    void setPosition(float x, float y);
};

// a basic shape for drawing, base for more advanced objects
class Frame {
protected:

    sf::ConvexShape frame;
    Content* content;

public:

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, sf::Color borderColor,
        uint8_t borderWidth);

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
        sf::Color borderColor, uint8_t borderWidth, 
        sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize);

    virtual void draw(sf::RenderWindow& window);

    Frame();

    ~Frame();

};

#endif