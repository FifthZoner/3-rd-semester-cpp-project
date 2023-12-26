#include <filesystem>

namespace fs = std::filesystem;

#include "loading.hpp"
#include "gameData.hpp"
#include "texturePacker.hpp"
#include "../graphics/elements/editorRender.hpp"
#include "settings.hpp"
#include "../parts.hpp"

std::vector <std::vector <ShipPart*>> shipParts;

void LoadParts(DataContainer& data){

    shipParts.resize(4);

    // structurals
    for (auto& entry : fs::directory_iterator("data/parts/structural/")){
        shipParts[0].push_back(new ShipPart(entry.path().string()));
    }
    // control
    for (auto& entry : fs::directory_iterator("data/parts/control/")){
        shipParts[1].push_back(new ShipControl(entry.path().string()));
    }
    // engines
    for (auto& entry : fs::directory_iterator("data/parts/engines/")){
        shipParts[2].push_back(new ShipEngine(entry.path().string()));
    }
    // reactors
    for (auto& entry : fs::directory_iterator("data/parts/reactors/")){
        shipParts[3].push_back(new ShipReactor(entry.path().string()));
    }


}

DataContainer LoadGame(){

    DataContainer data;

    if (!LoadFont("data/font/font.ttf")){
        // error here or whatever
    }

    setting::SetUIFont(&GetMainFont());

    LoadParts(data);

    RenderEditorPrepare();

    // packer must be after ALL texture loading, remember that in the future please - myself
    RunTexturePacking();

    // other checks
    if (setting::Resolution().x > 1280 and setting::Resolution().y > 720) {
        setting::editorScale = 1.5f * float(setting::Resolution().x) / 1280.f;
    }
    
    return data;
}