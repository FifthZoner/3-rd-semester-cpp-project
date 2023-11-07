#include "../../misc/settings.hpp"
#include "../../classes/gameData.hpp"
#include "../classes/graphicsLib.hpp"

// Graphical elements
Button buttonEditorPervious, buttonEditorNext;
Frame frameEditorStructuralText;
ScrollList scrollListEditorElements;

extern std::vector <std::vector <ShipPart*>> shipParts;

void RenderEditorPrepare(){
    buttonEditorPervious.create(sf::Vector2f(48, 48), sf::Vector2f(0, 0), setting::EditorBackgroundColor(), 
    setting::EditorBorderColor(), 6, setting::EditorBorderColor(), GetMainFont(), "<", 
    setting::EditorTextColor(), setting::EditorTextSize() * 2);

    buttonEditorNext.create(sf::Vector2f(48, 48), sf::Vector2f(192, 0), setting::EditorBackgroundColor(), 
    setting::EditorBorderColor(), 6, setting::EditorBorderColor(), GetMainFont(), ">", 
    setting::EditorTextColor(), setting::EditorTextSize() * 2);

    frameEditorStructuralText.create(sf::Vector2f(144, 48), sf::Vector2f(48, 0), setting::EditorBackgroundColor(), 
    setting::EditorBorderColor(), 6, GetMainFont(), "STRUCTURAL", 
    setting::EditorTextColor(), setting::EditorTextSize());

    scrollListEditorElements.create(shipParts, setting::GetUIStyle(), 
    sf::Vector2f(240, setting::Resolution().y - 48), sf::Vector2f(0, 48), sf::Vector2f(24, 48),
    sf::Vector2f(216, 60));

}

void RenderEditorMain(sf::RenderWindow& window){
    
}  

void RenderEditorList(sf::RenderWindow& window){
    buttonEditorNext.draw(window);
    buttonEditorPervious.draw(window);
    frameEditorStructuralText.draw(window);
    scrollListEditorElements.draw(window);
}
