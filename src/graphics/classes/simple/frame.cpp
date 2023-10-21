#include "frame.hpp"

Content::Content(){}

void Content::draw(sf::RenderWindow& window){}

void Content::setPosition(float x, float y){}

void ContentText::draw(sf::RenderWindow& window){
    window.draw(text);
}

ContentText::ContentText(sf::Font& font, std::string text, sf::Color textColor, uint8_t textSize, sf::Vector2f position){
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(textColor);
    this->text.setCharacterSize(textSize);
    this->text.setPosition(position);

    // centering here
    this->text.setOrigin(this->text.getLocalBounds().width / 2 + this->text.getLocalBounds().left, 
    this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2);
}

void ContentText::setPosition(float x, float y){
    text.setPosition(x, y);
}

void Frame::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, sf::Color borderColor,
    uint8_t borderWidth){

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

    content = new Content();
}

void Frame::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
    sf::Color borderColor, uint8_t borderWidth, 
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

    content = new ContentText(font, text, textColor, textSize, 
    sf::Vector2f(position.x + (size.x / 2), position.y + (size.y / 2)));
}

void Frame::draw(sf::RenderWindow& window){
    window.draw(frame);
    content->draw(window);
}

Frame::Frame(){
    content = nullptr;
    frame = sf::ConvexShape();
}

Frame::~Frame(){
    if (content != nullptr){
        delete content;
        content = nullptr;
    }
}
