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
            std::cout << "Got next one...\n";

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

}