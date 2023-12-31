#include "frame.hpp"
#include "../../../misc/texturePacker.hpp"

extern std::vector <Texturable*> affectedTexturables;

Content::Content(){}

Content::~Content(){}

void Content::draw(sf::RenderWindow& target){}
void Content::draw(sf::RenderTexture& target){}

void Content::setPosition(float x, float y){}

void ContentText::draw(sf::RenderWindow& target){
    target.draw(text);
}
void ContentText::draw(sf::RenderTexture& target){
    target.draw(text);
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

ContentText::ContentText(){}

void ContentText::setPosition(float x, float y){
    text.setPosition(x, y);
}

void ContentImage::draw(sf::RenderWindow& target){
    target.draw(sprite);
}

void ContentImage::draw(sf::RenderTexture& target){
    target.draw(sprite);
}

ContentImage::ContentImage(sf::Vector2f size, sf::Vector2f position, Texturable* donor){
    this->size = size;
    sprite.setPosition(position);
    donor->copyRectConfig(this);
}

ContentImage::ContentImage(sf::Vector2f size, sf::Vector2f position, std::string path){
    this->size = size;
    sprite.setPosition(position);
    loadTextureStandalone(path);
}

void ContentImage::setPosition(float x, float y){
    sprite.setPosition(x, y);
}

void ContentImage::setTexture(){
    sprite.setTexture(GetMainTexture());
    sprite.setTextureRect(*textureRect);
    //sprite.setScale(size.x / float(textureRect->width), size.y / float(textureRect->height));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

ContentImage::ContentImage(){}

ContentImage::~ContentImage(){}

void ContentBoth::draw(sf::RenderWindow& target){
    target.draw(sprite);
    target.draw(text);
}

void ContentBoth::draw(sf::RenderTexture& target){
    target.draw(sprite);
    target.draw(text);

}

ContentBoth::ContentBoth(sf::Vector2f& size, sf::Vector2f& textPosition, sf::Vector2f& imagePosition, Texturable* donor, UIStyle& style, std::string& text, sf::Vector2f position){
    this->size = size;
    sprite.setPosition(imagePosition + position);
    donor->copyRectConfig(this);

    this->text.setFont(*style.font);
    this->text.setString(text);
    this->text.setFillColor(style.textColor);
    this->text.setCharacterSize(style.descSize);
    this->text.setPosition(textPosition + position);

    // centering here
    this->text.setOrigin(this->text.getLocalBounds().width / 2 + this->text.getLocalBounds().left, 
    this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2);
}

ContentBoth::ContentBoth(sf::Vector2f& size, sf::Vector2f& textPosition, sf::Vector2f& imagePosition, std::string path, UIStyle& style, std::string& text, sf::Vector2f position){
    this->size = size;
    sprite.setPosition(imagePosition + position);
    loadTextureStandalone(path);

    this->text.setFont(*style.font);
    this->text.setString(text);
    this->text.setFillColor(style.textColor);
    this->text.setCharacterSize(style.descSize);
    this->text.setPosition(textPosition + position);

    // centering here
    this->text.setOrigin(this->text.getLocalBounds().width / 2 + this->text.getLocalBounds().left, 
    this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2);
}

ContentBoth::ContentBoth(){}

ContentBoth::~ContentBoth(){}

void ContentBoth::setPosition(float x, float y){
    sprite.setPosition(x, y);
    text.setPosition(x + textOffset.x, y + textOffset.y);
}

void Frame::create(sf::Vector2f size, sf::Vector2f position, UIStyle& style){

    // rectangle shape
    frame.setPointCount(4);
    frame.setPoint(0, sf::Vector2f(style.borderWidth, style.borderWidth));
    frame.setPoint(1, sf::Vector2f(size.x - style.borderWidth, style.borderWidth));
    frame.setPoint(2, sf::Vector2f(size.x - style.borderWidth, size.y - style.borderWidth));
    frame.setPoint(3, sf::Vector2f(style.borderWidth, size.y - style.borderWidth));
    
    // other stuff
    frame.setPosition(position);
    frame.setFillColor(style.backgroundColor);
    frame.setOutlineColor(style.borderColor);
    frame.setOutlineThickness(style.borderWidth);

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

void Frame::create(sf::Vector2f size, sf::Vector2f position, sf::Vector2f TextOffset, std::string text, 
        UIStyle& style, sf::Vector2f imageSize, sf::Vector2f imageOffset, std::string path){
            
}


void Frame::create(sf::Vector2f size, sf::Vector2f position, sf::Vector2f TextOffset, std::string text,
UIStyle& style, sf::Vector2f imageSize, sf::Vector2f imageOffset, Texturable* textureDonor){
    // rectangle shape
    frame.setPointCount(4);
    frame.setPoint(0, sf::Vector2f(style.borderWidth, style.borderWidth));
    frame.setPoint(1, sf::Vector2f(size.x - style.borderWidth, style.borderWidth));
    frame.setPoint(2, sf::Vector2f(size.x - style.borderWidth, size.y - style.borderWidth));
    frame.setPoint(3, sf::Vector2f(style.borderWidth, size.y - style.borderWidth));
    
    // other stuff
    frame.setPosition(position);
    frame.setFillColor(style.backgroundColor);
    frame.setOutlineColor(style.borderColor);
    frame.setOutlineThickness(style.borderWidth);
    
    content = new ContentBoth(size, TextOffset, imageOffset, textureDonor, style, text, position);
}

void Frame::draw(sf::RenderWindow& target){
    target.draw(frame);
    content->draw(target);
}

void Frame::draw(sf::RenderTexture& target){
    target.draw(frame);
    content->draw(target);
}

void Frame::setBackground(sf::Color color){
    frame.setFillColor(color);
}

Frame::Frame(){
    content = nullptr;
    frame = sf::ConvexShape();
}

Frame::~Frame(){}
