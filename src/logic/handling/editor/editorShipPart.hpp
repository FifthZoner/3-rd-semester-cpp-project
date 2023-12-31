#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_EDITORSHIPPART_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_EDITORSHIPPART_HPP

#include "../../classes/part.hpp"
#include <array>

struct EditorShipPart {
    ShipPart* partPointer = nullptr;
    sf::Sprite sprite;
    sf::Sprite points[4];
    EditorShipPart(ShipPart* part, sf::Vector2f position, unsigned int rotation = 0);
    void move(sf::Vector2f position, bool snap = false);
    // 1 is 90 degrees
    void rotate(int8_t angle);
    bool isClicked(sf::Vector2i position);
    void draw(sf::RenderWindow& target);
    void drawPoints(sf::RenderWindow& target);
    void draw(sf::RenderTexture& target);
    void drawPoints(sf::RenderTexture& target);
};

inline std::vector <EditorShipPart> editorParts;
inline std::array <std::vector <EditorShipPart>, 1> shipTemplates;

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_EDITORSHIPPART_HPP
