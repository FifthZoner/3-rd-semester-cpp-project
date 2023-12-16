#include "scrollList.hpp"

void ScrollListElement::create(Texturable* texturable, UIStyle& style, 
    sf::Vector2f position, sf::Vector2f size){

    element = texturable;
    idleColor = style.backgroundColor;
    clickedColor = style.clickedColor;

    frame.create(size, position, sf::Vector2f(0.75 * size.x, 0.5 * size.y), reinterpret_cast<ShipPart*>(element)->getName() + "\n<something>", 
    style, sf::Vector2f(size.x - (style.borderWidth * 2), size.x - (style.borderWidth * 2)), sf::Vector2f(0.25 * size.x, 0.5 * size.y), element);
}

void ScrollListElement::draw(sf::RenderTexture& target){
    frame.draw(target);
}

Texturable* ScrollListElement::getTexturable(){
    return element;
}

void ScrollListElement::setClicked(){
    frame.setBackground(clickedColor);
}

void ScrollListElement::setUnclicked(){
    frame.setBackground(idleColor);
}

ScrollListElement::ScrollListElement(){
}

ScrollListElement::~ScrollListElement(){
}

void ScrollList::create(std::vector <std::vector <ShipPart*>>& parts, UIStyle& style, 
sf::Vector2f size, sf::Vector2f position, sf::Vector2f scrollSize, sf::Vector2f tileSize){

    // render texture
    area.create(size.x - scrollSize.x, size.y);
    view.setSize(float(area.getSize().x), float(area.getSize().y));
    view.setCenter(float(area.getSize().x) / 2, float(area.getSize().y) / 2);
    area.setView(view);
    sprite.setPosition(position);

    // slider
    scroll.create(scrollSize, 
    sf::Vector2f(position.x + size.x - scrollSize.x, position.y), 
    style.backgroundColor, style.borderColor, style.borderWidth, style.clickedColor,  
    sf::FloatRect(position.x + size.x - (scrollSize.x / 2), position.y + (scrollSize.y / 2), 
    0, size.y - scrollSize.y));

    // elements
    elements.resize(parts.size());
    for (uint16_t n = 0; n < parts.size(); n++){
        elements[n].resize(parts[n].size());
        for (uint16_t m = 0; m < parts[n].size(); m++){
            elements[n][m].create(parts[n][m], style, sf::Vector2f(0.f, float(m) * tileSize.y), tileSize);
        }
    }
    currentList = 0;
    length = (elements[0].size() - 1) * tileSize.y;
    offset = 0;
    amountToRender = int(area.getSize().y / tileSize.y) + 1;
    tileHeight = tileSize.y;
}

void ScrollList::nextList(){
    if (currentList == elements.size() - 1){
        currentList = 0;
        return;
    }
    else {
        currentList++;
    }
    length = (elements[currentList].size() - 1) * tileHeight;
}


void ScrollList::perviousList(){
    if (currentList == 0){
        currentList = elements.size() - 1;
    }
    else {
        currentList--;
    }
}

void ScrollList::draw(sf::RenderWindow& target, sf::Vector2i mousePosition){
    area.clear(sf::Color(0, 0, 0, 0));

    if (clicked == clickState::bar) {
        offset = (int((elements[currentList].size() > int(area.getSize().y / tileHeight)) ? 
        elements[currentList].size() - int(area.getSize().y / tileHeight) : 0) * tileHeight * scroll.getPart(mousePosition).y);
    }

    // elements here
    sf::Vector2i renderBounds = sf::Vector2i(offset / tileHeight - 2, offset / tileHeight + amountToRender);
    if (renderBounds.y > elements[currentList].size()){
        //renderBounds.x -= renderBounds.y - elements[currentList].size();
        renderBounds.y = elements[currentList].size();
        if (renderBounds.x < 0){
            renderBounds.x = 0;
        }
    }

    for (int n = renderBounds.x; n < renderBounds.y; n++){
       elements[currentList][n].draw(area);
    }
    view.setCenter(view.getCenter().x, offset + (area.getSize().y / 2));
    area.setView(view);
    
    area.display();
    sprite.setTexture(area.getTexture());
    target.draw(sprite);
    scroll.draw(target);
}

bool ScrollList::isClicked(sf::Vector2i position){

    position -= sf::Vector2i(sprite.getPosition());

    // already clicked handling
    if (clicked != clickState::no) {
        if (clicked == clickState::bar) {
            // bar is clicked
            scroll.checkClick(position + sf::Vector2i(sprite.getPosition()));
            clicked = clickState::no;
            return false;
        }
        else {
            clicked = clickState::no;
            elements[clickIndex.x][clickIndex.y].setUnclicked();
            // list element is clicked
            if (position.x >= 0 and position.x <= area.getSize().x
                and position.y >= 0 and position.y <= area.getSize().y
                and position.y >= clickIndex.y * tileHeight - offset and position.y <= (clickIndex.y + 1) * tileHeight - offset ){
                return true;
            }
            return false;
        }
    }
    else {
        // tiles
        if (position.x >= 0 and position.x <= area.getSize().x
        and position.y >= 0 and position.y <= area.getSize().y){
            sf::Vector2i candidates(int(offset / tileHeight), int(offset / tileHeight) + int(area.getSize().y / tileHeight));
            if (candidates.x < 0){
                candidates.x = 0;
            }
            if (candidates.y >= elements[currentList].size()){
                candidates.y = elements[currentList].size() - 1;
            }

            // actual handling here
            for (uint32_t n = candidates.x; n <= candidates.y; n++){
                if (position.y >= n * tileHeight - offset and position.y <= (n + 1) * tileHeight - offset){
                    clicked = clickState::tile;
                    clickIndex.x = currentList;
                    clickIndex.y = n;
                    elements[clickIndex.x][clickIndex.y].setClicked();
                    return true;
                }
            }
        }
        


        // scroll thingy
        if (scroll.checkClick(position + sf::Vector2i(sprite.getPosition()))){
            clicked = clickState::bar;
            return true; // false to avoid interpreting as if a tile pressed
        }
    }

    

    return false;
}

Texturable* ScrollList::getLastTileClicked(){
    return elements[clickIndex.x][clickIndex.y].getTexturable();
}

ScrollList::ScrollList()= default;
    
ScrollList::~ScrollList()= default;

uint8_t ScrollList::getCurrentTab() const {
    return currentList;
}
