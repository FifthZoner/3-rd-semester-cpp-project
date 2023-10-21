#include "sliderButton.hpp"

void SliderButton::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, sf::Color borderColor,
        uint8_t borderWidth, sf::Color clickedBackgroundColor, sf::Rect <float> allowedRange){
        
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
    allowed = allowedRange;

    content = new Content();
}

void SliderButton::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
    sf::Color borderColor, uint8_t borderWidth, sf::Color clickedBackgroundColor, 
    sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize, sf::Rect <float> allowedRange){

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
    allowed = allowedRange;

    content = new ContentText(font, text, textColor, textSize, 
    sf::Vector2f(position.x + (size.x / 2), position.y + (size.y / 2)));
}

    // pass mouse position relative to the window
    // also updates the object, this might get moved into rendering for better fluidity but might not be required
sf::Vector2i SliderButton::getPosition(sf::Vector2i position){
    
    // calculating position closest to the bounds
    if (position.x < allowed.left){
        position.x = allowed.left;
    }
    if (position.y < allowed.top){
        position.y = allowed.top;
    }
    if (position.x > allowed.left + allowed.width){
        position.x = allowed.left + allowed.width;
    }
    if (position.y > allowed.top + allowed.height){
        position.y = allowed.top + allowed.height;
    }

    // moving the button the this position
    frame.setPosition(float(position.x) - (frame.getLocalBounds().width / 2), float(position.y) - (frame.getLocalBounds().height / 2));
    content->setPosition(float(position.x), float(position.y));
    
    return position;
}

SliderButton::SliderButton(){
    content = nullptr;
    frame = sf::ConvexShape();
    idleColor = sf::Color(0, 0, 0, 0);
    clickedColor = sf::Color(0, 0, 0, 0);
    isClicked = false;
    allowed = sf::Rect <float> (0, 0, 0, 0);
}

SliderButton::~SliderButton(){
    if (content != nullptr){
        delete content;
        content = nullptr;
    }
}