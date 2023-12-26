#ifndef EDITOR_RENDER_HPP
#define EDITOR_RENDER_HPP

#include <SFML/Graphics.hpp>

#include "../../misc/settings.hpp"
#include "../../classes/gameData.hpp"
#include "../classes/graphicsLib.hpp"

// Graphical elements
inline Button buttonEditorPrevious, buttonEditorNext, buttonEditorStart;
inline Frame frameEditorStructuralText, frameEditorControlText, frameEditorEngineText, frameEditorReactorText, frameEditorTopBar;
inline ScrollList scrollListEditorElements;

// Texture storage
inline Texturable textureEditorAttachmentPoint;
inline Texturable textureEditorRestrictedPoint;

void RenderEditorPrepare();

void RenderEditorMain(sf::RenderWindow& window);

void RenderEditorList(sf::RenderWindow& window);

#endif