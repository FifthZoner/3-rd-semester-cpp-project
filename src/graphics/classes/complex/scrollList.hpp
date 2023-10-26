#ifndef SCROLL_LIST_HPP
#define SCROLL_LIST_HPP

#include <vector>

#include "../simple/sliderButton.hpp"
#include "../simple/texturable.hpp"
#include "../../../misc/settings.hpp"
#include "../../../classes/part.hpp"

class ScrollListElement : public Button{
private:

    // intended layout as of now
    //
    //      iiii    ttt
    //      iiii    ttt
    //      iiii    ttt
    //
    // with more info when hovered over

    Frame frame;
    Texturable* element;
public:

    void create(Texturable* texturable, UIStyle& style, sf::Vector2f& position, sf::Vector2f& size);

    // checks and prepares the textbox for rendering new things, TODO
    bool isHoveredOver(sf::Vector2i& position);

    void draw(sf::RenderTexture& target);

    Texturable* getTexturable();
};

// A complex class to define a scrollable list, most notably the elements in the editor
class ScrollList {
protected:
    SliderButton scroll;
    std::vector <std::vector <ScrollListElement>> elements;
    sf::RenderTexture area;
    sf::Sprite sprite;
    sf::View view;
public:
    void create(std::vector <std::vector <ShipPart*>>& parts, UIStyle& style, 
        sf::Vector2f size, sf::Vector2f position);

    void draw(sf::RenderTarget& window);

    // handles all the clicking on it's own
    bool isClicked();

};

#endif