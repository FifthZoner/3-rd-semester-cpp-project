#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>

namespace setting{

    // returns true if successful, false otherwise
    bool LoadSettings(std::string path);

    bool IsRunning();
    void IsRunning(bool value);

    sf::Vector2i Resolution();
    void Resolution(sf::Vector2i value);

    uint8_t WindowStyle();
    void WindowStyle(uint8_t value);

    uint16_t Framerate();
    void Framerate(uint16_t value);

    sf::Color EditorBackgroundColor();
    void EditorBackgroundColor(sf::Color value);

    sf::Color EditorBorderColor();
    void EditorBorderColor(sf::Color value);

    sf::Color EditorTextColor();
    void EditorTextColor(sf::Color value);

    uint8_t EditorTextSize();
    void EditorTextSize(uint8_t value);

}

#endif