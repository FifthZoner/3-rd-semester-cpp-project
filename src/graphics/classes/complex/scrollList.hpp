#ifndef SCROLL_LIST_HPP
#define SCROLL_LIST_HPP

#include <vector>

#include "../simple/sliderButton.hpp"
#include "../simple/texturable.hpp"

class ScrollListElement : public Texturable {
private:
    Frame frame;
public:

    void create();

    // checks and prepares the textbox for rendering new things
    bool isHoveredOver(sf::Vector2i& position);
};

// A complex class to define a scrollable list, most notably the elements in the editor
class ScrollList {
protected:
    SliderButton scroll;
    std::vector <ScrollListElement> elements;
public:
};

#endif