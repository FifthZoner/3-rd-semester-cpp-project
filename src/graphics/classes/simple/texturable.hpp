#ifndef TEXTURABLE_HPP
#define TEXTURABLE_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "../../../misc/texturePacker.hpp"

// this is a primitive class, DO NOT USE for anything other than storage for more complex implementations, implement path getting
class Texturable {
protected:
    // rect is a pointer to allow for using the same texture on many objects
    sf::IntRect* textureRect;
    
public:

    // DO NOT pass a class with filled rect you need
    void copyRectConfig(Texturable* target);
    
    // DO NOT pass anything before texture packer has run
    void copyRect(Texturable* target);

    // this will do anyting only in classes with texturable sfml objects, so in parts it will be skipped
    virtual void setTexture();

    // Seriously do not use this in base class
    void loadTextureStandalone(const std::string& path);

    // copies the rect data to given texture
    void setSprite(sf::Sprite& sprite);

    Texturable();

    virtual ~Texturable();

};

#endif