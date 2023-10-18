#include <filesystem>

namespace fs = std::filesystem;

#include "loading.hpp"

void LoadParts(DataContainer& data){

    // structurals
    for (auto& entry : fs::directory_iterator("data/parts/structural/")){
        data.structurals.push_back(ShipPart(entry.path().string()));
    }



}

DataContainer LoadGame(){

    DataContainer data;

    GameData graphicsData;

    //graphicsData.font.loadFromFile("data/font/font.ttf");

    LoadParts(data);


    return data;
}