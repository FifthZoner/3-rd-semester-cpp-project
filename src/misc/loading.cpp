#include <filesystem>

namespace fs = std::filesystem;

#include "loading.hpp"
#include "gameData.hpp"
#include "texturePacker.hpp"
#include "../graphics/elements/editorRender.hpp"

std::vector <std::vector <ShipPart*>> shipParts;

void LoadParts(DataContainer& data){

    shipParts.resize(1);

    // structurals
    for (auto& entry : fs::directory_iterator("data/parts/structural/")){
        shipParts[0].push_back(new ShipPart(entry.path().string()));
    }



}

DataContainer LoadGame(){

    DataContainer data;

    if (!LoadFont("data/font/font.ttf")){
        // error here or whatever
    }

    LoadParts(data);

    RunTexturePacking();

    RenderEditorPrepare();
    
    return data;
}