#include <fstream>
#include <vector>
#include <iostream>

#include "settings.hpp"
#include "misc.hpp"


namespace setting{

    namespace{
        bool isRunning = true;
        sf::Vector2i resolution = sf::Vector2i(800, 600);
        uint8_t windowStyle = sf::Style::Default;
        uint16_t framerate = 60;
    }

    bool LoadSettings(std::string path){

        std::ifstream file;
        file.open(path);

        if (!file.is_open()){
            return false;
        }

        while (!file.eof()){
            std::string input;
            std::getline(file, input);

            if (input.length() > 0 and input[0] == '#'){
                continue;
            }

            auto split = SplitString(input, ' ');
            
            if (split.size() == 2){
                if (split[0] == "windowStyle"){
                    if (split[1] == "Default"){
                        WindowStyle(sf::Style::Default);
                    }
                    else if (split[1] == "Fullscreen"){
                        WindowStyle(sf::Style::Fullscreen);
                    }
                    else if (split[1] == "None"){
                        WindowStyle(sf::Style::None);
                    }
                    else if (split[1] == "Titlebar"){
                        WindowStyle(sf::Style::Titlebar);
                    }
                    else if (split[1] == "Resize"){
                        WindowStyle(sf::Style::Resize);
                    }
                }
                else if (split[0] == "framerate"){
                    Framerate(std::stoi(split[1]));
                }

            }
            else if (split.size() == 3){
                if (split[0] == "resolution"){
                    Resolution(sf::Vector2i(stoi(split[1]), stoi(split[2])));
                }
            }
        }

        return true;
    }

    bool IsRunning(){
        return isRunning;
    }
    void IsRunning(bool value){
        isRunning = value;
    }

    sf::Vector2i Resolution(){
        return resolution;
    }
    void Resolution(sf::Vector2i value){
        resolution = value;
    }

    uint8_t WindowStyle(){
        return windowStyle;
    }
    void WindowStyle(uint8_t value){
        windowStyle = value;
    }

    uint16_t Framerate(){
        return framerate;
    }
    void Framerate(uint16_t value){
        framerate = value;
    }

    sf::Color editorBackgroundColor = sf::Color(32, 32, 32, 255);
    sf::Color EditorBackgroundColor(){
        return editorBackgroundColor;
    }
    void EditorBackgroundColor(sf::Color value){
        editorBackgroundColor = value;
    }

    sf::Color editorBorderColor = sf::Color(48, 48, 48, 255);
    sf::Color EditorBorderColor(){
        return editorBorderColor;
    }
    void EditorBorderColor(sf::Color value){
        editorBorderColor = value;
    }

    sf::Color editorTextColor = sf::Color(255, 255, 255, 255);
    sf::Color EditorTextColor(){
        return editorTextColor;
    }
    void EditorTextColor(sf::Color value){
        editorTextColor = value;
    }

    uint8_t editorTextSize = 20;
    uint8_t EditorTextSize(){
        return editorTextSize;
    }
    void EditorTextSize(uint8_t value){
        editorTextSize = value;
    }
}