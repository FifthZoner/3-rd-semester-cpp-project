#include "frame.hpp"
#include "../../../misc/texturePacker.hpp"

extern std::vector <Texturable*> affectedTexturables;

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

void ContentImage::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

ContentImage::ContentImage(sf::Vector2f size, sf::Vector2f position, Texturable* donor){
    this->size = size;
    sprite.setPosition(position);
    donor->copyRect(this);
}

ContentImage::ContentImage(sf::Vector2f size, sf::Vector2f position, std::string path){
    this->size = size;
    sprite.setPosition(position);
    loadTextureStandalone(path);
}

void ContentImage::loadTextureStandalone(std::string path){
    textureRect = new sf::IntRect;
    AddTextureToPack(path, textureRect);
    affectedTexturables.push_back(this);
}

void ContentImage::setPosition(float x, float y){
    sprite.setPosition(x, y);
}

void ContentImage::setTexture(){
    sprite.setTexture(GetMainTexture());
    sprite.setTextureRect(*textureRect);
    sprite.setScale(size.x / float(textureRect->width), size.y / float(textureRect->height));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
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

void Frame::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
    sf::Color borderColor, uint8_t borderWidth, sf::Vector2f imageSize, sf::Vector2f imageOffset, std::string path){

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

        content = new ContentImage(imageSize, sf::Vector2f(position.x + (size.x / 2) + imageOffset.x, position.y + (size.y / 2) + imageOffset.y), path);
    }

void Frame::create(sf::Vector2f size, sf::Vector2f position, sf::Color backgroundColor, 
    sf::Color borderColor, uint8_t borderWidth, sf::Vector2f imageSize, sf::Vector2f imageOffset, Texturable* textureDonor){

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

        content = new ContentImage(imageSize, sf::Vector2f(position.x + (size.x / 2) + imageOffset.x, position.y + (size.y / 2) + imageOffset.y), textureDonor);
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
