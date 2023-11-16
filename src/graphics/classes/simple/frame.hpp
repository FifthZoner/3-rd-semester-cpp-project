#ifndef FRAME_HPP
#define FRAME_HPP

#include <SFML/Graphics.hpp>

#include "texturable.hpp"
#include "../../misc/settings.hpp"

// empty
class Content {
public:

    virtual void draw(sf::RenderWindow& target);
    virtual void draw(sf::RenderTexture& target);

    virtual void setPosition(float x, float y);

    Content();

    virtual ~Content();
};

class ContentText : public Content {
protected:

    sf::Text text;

public:

    virtual void draw(sf::RenderWindow& target);
    virtual void draw(sf::RenderTexture& target);

    // for now no alignment options, pass the position in the middle of the button
    ContentText(sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize, sf::Vector2f position);

    ContentText();

    virtual void setPosition(float x, float y);
};

// load a standalone texture or copy it from another Texturable object
class ContentImage : public Content, public Texturable {
protected:

    sf::Sprite sprite;
    sf::Vector2f size;

public:

    virtual void draw(sf::RenderWindow& target);
    virtual void draw(sf::RenderTexture& target);

    ContentImage(sf::Vector2f size, sf::Vector2f position, Texturable* donor);

    ContentImage(sf::Vector2f size, sf::Vector2f position, std::string path);

    ContentImage();
    
    virtual ~ContentImage();

    virtual void setPosition(float x, float y);

    void setTexture();
};

class ContentBoth : public ContentImage {

    sf::Vector2f textOffset;
    sf::Text text;

public:
    void draw(sf::RenderWindow& target);
    void draw(sf::RenderTexture& target);

    ContentBoth(sf::Vector2f& size, sf::Vector2f& textPosition, sf::Vector2f& imagePosition, Texturable* donor, UIStyle& style, std::string& text, sf::Vector2f position);

    ContentBoth(sf::Vector2f& size, sf::Vector2f& textPosition, sf::Vector2f& imagePosition, std::string path, UIStyle& style, std::string& text, sf::Vector2f position);

    ContentBoth();

    ~ContentBoth();

    // pass image position
    void setPosition(float x, float y);

};

// a basic shape for drawing, base for more advanced objects
class Frame {
protected:

    sf::ConvexShape frame;
    Content* content;

public:

    virtual void create(sf::Vector2f size, sf::Vector2f position, UIStyle& style);

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
        sf::Color borderColor, uint8_t borderWidth, 
        sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize);

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
        sf::Color borderColor, uint8_t borderWidth, sf::Vector2f imageSize, sf::Vector2f imageOffset, std::string path);

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
        sf::Color borderColor, uint8_t borderWidth, sf::Vector2f imageSize, sf::Vector2f imageOffset, Texturable* textureDonor);

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Vector2f TextOffset, std::string text, 
        UIStyle& style, sf::Vector2f imageSize, sf::Vector2f imageOffset, std::string path);

    virtual void create(sf::Vector2f size, sf::Vector2f position, sf::Vector2f TextOffset, std::string text,
        UIStyle& style, sf::Vector2f imageSize, sf::Vector2f imageOffset, Texturable* textureDonor);

    virtual void draw(sf::RenderWindow& target);
    virtual void draw(sf::RenderTexture& target);

    void setBackground(sf::Color color);

    Frame();

    ~Frame();

};

#endif