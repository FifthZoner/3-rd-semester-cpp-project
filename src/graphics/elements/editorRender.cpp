#include "../../misc/settings.hpp"
#include "../../classes/gameData.hpp"
#include "../classes/graphicsLib.hpp"

// Graphical elements
Button buttonEditorPervious, buttonEditorNext, buttonEditorStart;
Frame frameEditorStructuralText, frameEditorTopBar;
ScrollList scrollListEditorElements;

// Texture storage
Texturable textureEditorAttachmentPoint;

extern std::vector <std::vector <ShipPart*>> shipParts;

void RenderEditorPrepare(){
    buttonEditorPervious.create(sf::Vector2f(48, 48), sf::Vector2f(0, 0), setting::EditorBackgroundColor(), 
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

    textureEditorAttachmentPoint.loadTextureStandalone("data/textures/parts/other/attachmentPoint.png");

}

void RenderEditorMain(sf::RenderWindow& window){
    
}  

void RenderEditorList(sf::RenderWindow& window){
    buttonEditorNext.draw(window);
    buttonEditorPervious.draw(window);
    buttonEditorStart.draw(window);
    frameEditorStructuralText.draw(window);
    frameEditorTopBar.draw(window);
    scrollListEditorElements.draw(window, sf::Mouse::getPosition(window));
}
