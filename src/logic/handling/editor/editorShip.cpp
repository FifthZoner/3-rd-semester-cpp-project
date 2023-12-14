#include "editorShip.hpp"
#include "../../graphics/elements/editorRender.hpp"

EditorShipPart::EditorShipPart(ShipPart* part, sf::Vector2f position) {

    part->setSprite(sprite);

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

    move(position);
}

void EditorShipPart::move(sf::Vector2f position, bool snap) {
    if (snap) {
        // TODO: add snapping
    }

    sprite.setPosition(position);
    // getting the current angle and setting all the point positions accordingly
    auto angle = uint8_t(sprite.getRotation() / 90);
    points[0 + angle % 4].setPosition(position.x + sprite.getGlobalBounds().width * 0.25f,
                                      position.y - sprite.getGlobalBounds().height * 0.25f);
    points[1 + angle % 4].setPosition(position.x + sprite.getGlobalBounds().width * 0.75f,
                                      position.y + sprite.getGlobalBounds().height * 0.25f);
    points[2 + angle % 4].setPosition(position.x +  sprite.getGlobalBounds().width * 0.25f,
                                      position.y + sprite.getGlobalBounds().height * 0.75f);
    points[3 + angle % 4].setPosition(position.x - sprite.getGlobalBounds().width * 0.25f,
                                      position.y + sprite.getGlobalBounds().height * 0.25f);
}

void EditorShipPart::rotate(int8_t angle) {
    sprite.rotate(float(angle) * 90);

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