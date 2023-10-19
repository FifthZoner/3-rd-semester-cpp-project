#include "../../misc/settings.hpp"
#include "../../classes/gameData.hpp"
#include "../classes/button.hpp"

// Graphical elements
Button buttonEditorPervious, buttonEditorNext;

void DummyFunction(){}

void RenderEditorPrepare(){
    buttonEditorPervious.create(sf::Vector2f(48, 48), sf::Vector2f(0, 0), setting::EditorBackgroundColor(), 
    setting::EditorBorderColor(), &DummyFunction, 6, setting::EditorBorderColor(), GetMainFont(), "<", 
    setting::EditorTextColor(), setting::EditorTextSize() * 2);

    buttonEditorNext.create(sf::Vector2f(48, 48), sf::Vector2f(192, 0), setting::EditorBackgroundColor(), 
    setting::EditorBorderColor(), &DummyFunction, 6, setting::EditorBorderColor(), GetMainFont(), ">", 
    setting::EditorTextColor(), setting::EditorTextSize() * 2);
}

void RenderEditor(sf::RenderWindow& window){
    buttonEditorNext.draw(window);
    buttonEditorPervious.draw(window);
}  