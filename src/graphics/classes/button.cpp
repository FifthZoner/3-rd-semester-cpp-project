#include "button.hpp"

ButtonContent::ButtonContent(){}

void ButtonContent::draw(sf::RenderWindow& window){}

void ButtonText::draw(sf::RenderWindow& window){
    window.draw(text);
}

ButtonText::ButtonText(sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize, sf::Vector2f position){
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(textColor);
    this->text.setCharacterSize(textSize);
    this->text.setPosition(position);

    // centering here
    this->text.setOrigin(this->text.getLocalBounds().width / 2 + this->text.getLocalBounds().left, 
    this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2);
}

void Button::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, sf::Color borderColor,
    void (*function)(), uint8_t borderWidth, sf::Color clickedBackgroundColor){

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
    runFunction = function;
    idleColor = backgroundColor;
    clickedColor = clickedBackgroundColor;
    isClicked = false;

    content = new ButtonContent();
}

void Button::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
    sf::Color borderColor, void (*function)(), uint8_t borderWidth, sf::Color clickedBackgroundColor, 
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
    runFunction = function;
    idleColor = backgroundColor;
    clickedColor = clickedBackgroundColor;
    isClicked = false;

    content = new ButtonText(font, text, textColor, textSize, 
    sf::Vector2f(position.x + (size.x / 2), position.y + (size.y / 2)));
}

void Button::draw(sf::RenderWindow& window){
    window.draw(frame);
    content->draw(window);
}

Button::Button(){
    content = nullptr;
    runFunction = nullptr;
    frame = sf::ConvexShape();
    idleColor = sf::Color(0, 0, 0, 0);
    clickedColor = sf::Color(0, 0, 0, 0);
    isClicked = false;
}

Button::~Button(){
    if (content != nullptr){
        delete content;
    }
}

bool Button::checkClick(sf::Vector2f position){
    // ;-;
    return false;
}