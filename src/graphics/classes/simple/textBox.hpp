#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "frame.hpp"
#include "settings.hpp"

// a text box, only one will be declared
// does not use frame's text functions
class TextBox : public Frame {
private:
    std::string string;

public:

    // a base text box, no text
    void create(UIStyle& style);

    void setText(std::string text);

    void draw(sf::RenderWindow window);
};

#endif