#include <cmath>
#include "editorShipPart.hpp"
#include "../../graphics/elements/editorRender.hpp"

EditorShipPart::EditorShipPart(ShipPart* part, sf::Vector2f position, unsigned int rotation) {

    part->setSprite(sprite);
    partPointer = part;

    const MountPoints& temp = part->getMountPoints();
    switch (temp.frontPoint){
        case MountPoints::Type::present:
            textureEditorAttachmentPoint.setSprite(points[0]);
            break;
        case MountPoints::Type::restricted:
            textureEditorRestrictedPoint.setSprite(points[0]);
            break;
        default:
            break;
    }
    switch (temp.rightPoint){
        case MountPoints::Type::present:
            textureEditorAttachmentPoint.setSprite(points[1]);
            break;
        case MountPoints::Type::restricted:
            textureEditorRestrictedPoint.setSprite(points[1]);
            break;
        default:
            break;
    }
    switch (temp.backPoint){
        case MountPoints::Type::present:
            textureEditorAttachmentPoint.setSprite(points[2]);
            break;
        case MountPoints::Type::restricted:
            textureEditorRestrictedPoint.setSprite(points[2]);
            break;
        default:
            break;
    }
    switch (temp.leftPoint){
        case MountPoints::Type::present:
            textureEditorAttachmentPoint.setSprite(points[3]);
            break;
        case MountPoints::Type::restricted:
            textureEditorRestrictedPoint.setSprite(points[3]);
            break;
        default:
            break;
    }

    points[0].setScale(0.5f * setting::editorScale, 0.5f * setting::editorScale);
    points[1].setScale(0.5f * setting::editorScale, 0.5f * setting::editorScale);
    points[2].setScale(0.5f * setting::editorScale, 0.5f * setting::editorScale);
    points[3].setScale(0.5f * setting::editorScale, 0.5f * setting::editorScale);
    sprite.setScale(setting::editorScale, setting::editorScale);

    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    points[0].setOrigin(points[0].getLocalBounds().width / 2, points[0].getLocalBounds().height / 2 + sprite.getLocalBounds().height);
    points[1].setOrigin(points[1].getLocalBounds().width / 2 - sprite.getLocalBounds().width, points[1].getLocalBounds().height / 2);
    points[2].setOrigin(points[2].getLocalBounds().width / 2, points[2].getLocalBounds().height / 2 - sprite.getLocalBounds().height);
    points[3].setOrigin(points[3].getLocalBounds().width / 2 + sprite.getLocalBounds().width, points[3].getLocalBounds().height / 2);
    move(position, true);
    rotate(rotation);
}

void EditorShipPart::move(sf::Vector2f position, bool snap) {
    if (snap) {
        position.x = std::floor(position.x / (setting::editorScale * 32)) * setting::editorScale * 32;
        position.y = std::floor(position.y / (setting::editorScale * 32)) * setting::editorScale * 32;
    }

    sprite.setPosition(position);
    points[0].setPosition(position);
    points[1].setPosition(position);
    points[2].setPosition(position);
    points[3].setPosition(position);
}

void EditorShipPart::rotate(int8_t angle) {
    sprite.rotate(float(angle) * 90);
    points[0].rotate(float(angle) * 90);
    points[1].rotate(float(angle) * 90);
    points[2].rotate(float(angle) * 90);
    points[3].rotate(float(angle) * 90);

    move(sprite.getPosition());
}

bool EditorShipPart::isClicked(sf::Vector2i position) {
    if (float(position.x) >= sprite.getGlobalBounds().left and float(position.x) <= sprite.getGlobalBounds().left + sprite.getGlobalBounds().width and
        float(position.y) >= sprite.getGlobalBounds().top and float(position.y) <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) {
        return true;
    }
    return false;
}

void EditorShipPart::draw(sf::RenderWindow& target){
    target.draw(sprite);
}

void EditorShipPart::drawPoints(sf::RenderWindow& target){
    target.draw(points[0]);
    target.draw(points[1]);
    target.draw(points[2]);
    target.draw(points[3]);
}

void EditorShipPart::draw(sf::RenderTexture& target){
    target.draw(sprite);
}

void EditorShipPart::drawPoints(sf::RenderTexture& target){
    target.draw(points[0]);
    target.draw(points[1]);
    target.draw(points[2]);
    target.draw(points[3]);
}