#include "gameData.hpp"

namespace {
    sf::Font mainFont;
}

sf::Font& GetMainFont(){
    return mainFont;
    
}

bool LoadFont(std::string path){
    return mainFont.loadFromFile(path);
}