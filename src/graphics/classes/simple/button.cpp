#include "button.hpp"

void Button::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, sf::Color borderColor,
    uint8_t borderWidth, sf::Color clickedBackgroundColor){

    // rectangle shape
    frame.setPointCount(4);
    frame.setPoint(0, sf::Vector2f(borderWidth, borderWidth));
    frame.setPoint(1, sf::Vector2f(size.x - borderWidth, borderWidth));
    frame.setPoint(2, sf::Vector2f(size.x - borderWidth, size.y - borderWidth));
    frame.setPoint(3, sf::Vector2f(borderWidth, size.y - borderWidth));
    
    // other stuff
    frame.setPosition(position);
    frame.setFillColor(backgroundColor);
    frame.setOutlineColor(borderColor);
    frame.setOutlineThickness(borderWidth);
    idleColor = backgroundColor;
    clickedColor = clickedBackgroundColor;
    isClicked = false;

    content = new Content();
}

void Button::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
    sf::Color borderColor, uint8_t borderWidth, sf::Color clickedBackgroundColor, 
    sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize){

    // rectangle shape
    frame.setPointCount(4);
    frame.setPoint(0, sf::Vector2f(borderWidth, borderWidth));
    frame.setPoint(1, sf::Vector2f(size.x - borderWidth, borderWidth));
    frame.setPoint(2, sf::Vector2f(size.x - borderWidth, size.y - borderWidth));
    frame.setPoint(3, sf::Vector2f(borderWidth, size.y - borderWidth));
    
    // other stuff
    frame.setPosition(position);
    frame.setFillColor(backgroundColor);
    frame.setOutlineColor(borderColor);
    frame.setOutlineThickness(borderWidth);
    idleColor = backgroundColor;
    clickedColor = clickedBackgroundColor;
    isClicked = false;

    content = new ContentText(font, text, textColor, textSize, 
    sf::Vector2f(position.x + (size.x / 2), position.y + (size.y / 2)));
}

void Button::draw(sf::RenderWindow& window){
    window.draw(frame);
    content->draw(window);
}

Button::Button(){
    content = nullptr;
    frame = sf::ConvexShape();
    idleColor = sf::Color(0, 0, 0, 0);
    clickedColor = sf::Color(0, 0, 0, 0);
    isClicked = false;
}

Button::~Button(){
    if (content != nullptr){
        delete content;
        content = nullptr;
    }
}

// pass a window relative position
bool Button::checkClick(const sf::Vector2i& position){
    
    if (!isClicked){
        if (position.x < frame.getGlobalBounds().left){
            return false;
        }
        if (position.y < frame.getGlobalBounds().top){
            return false;
        }
        if (position.x > frame.getGlobalBounds().left + frame.getGlobalBounds().width){
            return false;
        }
        if (position.y > frame.getGlobalBounds().top + frame.getGlobalBounds().height){
            return false;
        }

        isClicked = true;
        frame.setFillColor(clickedColor);
        return true;
    }

    isClicked = false;
    frame.setFillColor(idleColor);

    if (position.x < frame.getGlobalBounds().left){
        return false;
    }
    if (position.y < frame.getGlobalBounds().top){
        return false;
    }
    if (position.x > frame.getGlobalBounds().left + frame.getGlobalBounds().width){
        return false;
    }
    if (position.y > frame.getGlobalBounds().top + frame.getGlobalBounds().height){
        return false;
    }

    return true;
}