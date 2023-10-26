#include "scrollList.hpp"

void ScrollListElement::create(Texturable* texturable, UIStyle& style, 
    sf::Vector2f& position, sf::Vector2f& size){

    element = texturable;

    frame.create(size, position, sf::Vector2f(0,0), reinterpret_cast<ShipPart*>(element)->getName(), 
    style, sf::Vector2f(32, 32), sf::Vector2f(0, 0), element);
}

bool ScrollListElement::isHoveredOver(sf::Vector2i& position){
    return false;
}

void ScrollListElement::draw(sf::RenderTexture& target){
    frame.draw(target);
}

Texturable* ScrollListElement::getTexturable(){
    return element;
}

void ScrollList::create(std::vector <std::vector <ShipPart*>>& parts, UIStyle& style, 
    sf::Vector2f size, sf::Vector2f position){

}

void ScrollList::draw(sf::RenderTarget target){
    // this will be annoying
}

bool ScrollList::isClicked(){



    return false;
}