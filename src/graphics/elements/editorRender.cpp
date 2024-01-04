#include <iostream>
#include "editorRender.hpp"
#include "../../logic/handling/editor/editorShipPart.hpp"
#include "editorHandling.hpp"

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

    frameEditorControlText.create(sf::Vector2f(144, 48), sf::Vector2f(48, 0), setting::EditorBackgroundColor(),
                                  setting::EditorBorderColor(), 6, GetMainFont(), "CONTROL",
                                  setting::EditorTextColor(), setting::EditorTextSize());

    frameEditorEngineText.create(sf::Vector2f(144, 48), sf::Vector2f(48, 0), setting::EditorBackgroundColor(),
                                 setting::EditorBorderColor(), 6, GetMainFont(), "ENGINES",
                                 setting::EditorTextColor(), setting::EditorTextSize());

    frameEditorReactorText.create(sf::Vector2f(144, 48), sf::Vector2f(48, 0), setting::EditorBackgroundColor(),
                                 setting::EditorBorderColor(), 6, GetMainFont(), "REACTORS",
                                 setting::EditorTextColor(), setting::EditorTextSize());

    frameEditorWeaponText.create(sf::Vector2f(144, 48), sf::Vector2f(48, 0), setting::EditorBackgroundColor(),
                                  setting::EditorBorderColor(), 6, GetMainFont(), "WEAPONS",
                                  setting::EditorTextColor(), setting::EditorTextSize());


    frameEditorTopBar.create(sf::Vector2f(setting::Resolution().x - 336, 48), sf::Vector2f(240, 0), setting::GetUIStyle()); 

    scrollListEditorElements.create(shipParts, setting::GetUIStyle(), 
    sf::Vector2f(240, setting::Resolution().y - 48), sf::Vector2f(0, 48), sf::Vector2f(24, 48),
    sf::Vector2f(216, 60));

    textureEditorAttachmentPoint.loadTextureStandalone("data/textures/parts/other/free.png");
    textureEditorRestrictedPoint.loadTextureStandalone("data/textures/parts/other/restricted.png");

}

void RenderEditorMain(sf::RenderWindow& window){
    while (editorElementLock){
        sf::sleep(sf::microseconds(5));
    }
    editorElementLock = true;
    for (auto& n : editorParts) {
        n.drawPoints(window);
    }
    for (auto& n : editorParts) {
        n.draw(window);
    }
    editorElementLock = false;
}  

void RenderEditorList(sf::RenderWindow& window){
    buttonEditorNext.draw(window);
    buttonEditorPrevious.draw(window);
    buttonEditorStart.draw(window);
    switch (scrollListEditorElements.getCurrentTab()) {
        case 0:
            // structural
            frameEditorStructuralText.draw(window);
            break;
        case 1:
            // control
            frameEditorControlText.draw(window);
            break;
        case 2:
            // engines
            frameEditorEngineText.draw(window);
            break;
        case 3:
            // reactors
            frameEditorReactorText.draw(window);
            break;
        case 4:
            // weapons
            frameEditorWeaponText.draw(window);
            break;
        default:
            break;
    }
    frameEditorTopBar.draw(window);
    scrollListEditorElements.draw(window, sf::Mouse::getPosition(window));
}
