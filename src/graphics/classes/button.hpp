#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace {

    struct ButtonContent{

        virtual void render();

    };

}

class Button {
private:

    sf::RectangleShape frame;

    void (*runFunction)();

    ButtonContent content;

public:

    // this function changes the color, returns the bool AND handles the effect function
    bool checkClick(sf::Vector2f position);

    void create();

    Button();

    ~Button();

};

#endif