#include "editorRender.hpp"
#include "../../logic/handling/editor/editorShip.hpp"

extern std::vector <std::vector <ShipPart*>> shipParts;

void RenderEditorPrepare(){
    buttonEditorPrevious.create(sf::Vector2f(48, 48), sf::Vector2f(0, 0), setting::EditorBackgroundColor(),
                                setting::EditorBorderColor(), 6, setting::EditorBorderColor(), GetMainFont(), "<",
                                setting::EditorTextColor(), setting::EditorTextSize() * 2);

    buttonEditorNext.create(sf::Vector2f(48, 48), sf::Vector2f(192, 0), setting::EditorBackgroundColor(), 
    setting::EditorBorderColor(), 6, setting::EditorBorderColor(), GetMainFont(), ">", 
    setting::EditorTextColor(), setting::EditorTextSize() * 2);

    buttonEditorStart.create(sf::Vector2f(96, 48), sf::Vector2f(setting::Resolution().x - 96, 0), setting::EditorBackgroundColor(), 
    setting::EditorBorderColor(), 6, setting::EditorBorderColor(), GetMainFont(), "START", 
    setting::EditorTextColor(), setting::EditorTextSize());

    frameEditorStructuralText.create(sf::Vector2f(144, 48), sf::Vector2f(48, 0), setting::EditorBackgroundColor(), 
    setting::EditorBorderColor(), 6, GetMainFont(), "STRUCTURAL", 
    setting::EditorTextColor(), setting::EditorTextSize());

    frameEditorTopBar.create(sf::Vector2f(setting::Resolution().x - 336, 48), sf::Vector2f(240, 0), setting::GetUIStyle()); 

    scrollListEditorElements.create(shipParts, setting::GetUIStyle(), 
    sf::Vector2f(240, setting::Resolution().y - 48), sf::Vector2f(0, 48), sf::Vector2f(24, 48),
    sf::Vector2f(216, 60));

    textureEditorAttachmentPoint.loadTextureStandalone("data/textures/parts/other/free.png");
    textureEditorRestrictedPoint.loadTextureStandalone("data/textures/parts/other/restricted.png");

}

void RenderEditorMain(sf::RenderWindow& window){
    for (auto& n : editorParts) {
        n.drawPoints(window);
    }
    for (auto& n : editorParts) {
        n.draw(window);
    }
}  

void RenderEditorList(sf::RenderWindow& window){
    buttonEditorNext.draw(window);
    buttonEditorPrevious.draw(window);
    buttonEditorStart.draw(window);
    frameEditorStructuralText.draw(window);
    frameEditorTopBar.draw(window);
    scrollListEditorElements.draw(window, sf::Mouse::getPosition(window));
}
