#include <filesystem>
#include <random>

namespace fs = std::filesystem;

#include "loading.hpp"
#include "gameData.hpp"
#include "texturePacker.hpp"
#include "../graphics/elements/editorRender.hpp"
#include "settings.hpp"
#include "../parts.hpp"
#include "gameplayHandling.hpp"
#include "gameOverRenderer.hpp"
#include "ship.hpp"

void LoadParts(DataContainer& data){

    shipParts.resize(5);

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
    // weapons
    for (auto& entry : fs::directory_iterator("data/parts/weapons/")){
        shipParts[4].push_back(new ShipWeapon(entry.path().string()));
    }

}

sf::Vector2f ScaledCoords(float x, float y) {
    return sf::Vector2f(x, y) * 32.f * setting::editorScale;
}

void LoadShipTemplates() {

    //          C
    //      W E R E W
    //      S S R S S
    //      E S S S E
    //      S E E E S

    // cockpit
    shipTemplates[0].emplace_back(shipParts[1][0], ScaledCoords(3, 0), 0);
    // reactors
    shipTemplates[0].emplace_back(shipParts[3][0], ScaledCoords(3, 1), 0);
    shipTemplates[0].emplace_back(shipParts[3][0], ScaledCoords(3, 2), 0);
    // engines
    shipTemplates[0].emplace_back(shipParts[2][0], ScaledCoords(2, 1), 2);
    shipTemplates[0].emplace_back(shipParts[2][0], ScaledCoords(4, 1), 2);
    shipTemplates[0].emplace_back(shipParts[2][0], ScaledCoords(1, 3), 1);
    shipTemplates[0].emplace_back(shipParts[2][0], ScaledCoords(5, 3), 3);
    shipTemplates[0].emplace_back(shipParts[2][0], ScaledCoords(2, 4), 0);
    shipTemplates[0].emplace_back(shipParts[2][0], ScaledCoords(3, 4), 0);
    shipTemplates[0].emplace_back(shipParts[2][0], ScaledCoords(4, 4), 0);
    // weapons
    shipTemplates[0].emplace_back(shipParts[4][0], ScaledCoords(1, 1), 0);
    shipTemplates[0].emplace_back(shipParts[4][1], ScaledCoords(5, 1), 0);
    // structural
    shipTemplates[0].emplace_back(shipParts[0][0], ScaledCoords(2, 2), 0);
    shipTemplates[0].emplace_back(shipParts[0][8], ScaledCoords(1, 2), 2);
    shipTemplates[0].emplace_back(shipParts[0][0], ScaledCoords(4, 2), 0);
    shipTemplates[0].emplace_back(shipParts[0][6], ScaledCoords(5, 2), 2);
    shipTemplates[0].emplace_back(shipParts[0][0], ScaledCoords(2, 3), 0);
    shipTemplates[0].emplace_back(shipParts[0][0], ScaledCoords(3, 3), 0);
    shipTemplates[0].emplace_back(shipParts[0][0], ScaledCoords(4, 3), 0);
    shipTemplates[0].emplace_back(shipParts[0][7], ScaledCoords(5, 4), 1);
    shipTemplates[0].emplace_back(shipParts[0][4], ScaledCoords(1, 4), 3);
}

std::array <Texturable, 4> asteroidTextures;

#define ASTEROID_SAFE_AREA_SIZE 800
#define ASTEROID_AREA_SIZE 8000
#define ASTEROID_MIN_SCALE 6
#define ASTEROID_MAX_SCALE 24

DataContainer LoadGame(){

    DataContainer data;

    if (!LoadFont("data/font/font.ttf")){
        // error here or whatever
    }

    setting::SetUIFont(&GetMainFont());

    LoadParts(data);

    RenderEditorPrepare();

    // game over screen
    gameOverText.setFont(GetMainFont());
    gameOverText.setCharacterSize(80);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(10);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(sf::Vector2f(setting::Resolution() / 2));
    gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2 + gameOverText.getLocalBounds().left,
                           gameOverText.getLocalBounds().top + gameOverText.getLocalBounds().height / 2);


            // preparing asteroids
    asteroidTextures[0].loadTextureStandalone("data/textures/asteroids/asteroid1.png");
    asteroidTextures[1].loadTextureStandalone("data/textures/asteroids/asteroid2.png");
    asteroidTextures[2].loadTextureStandalone("data/textures/asteroids/asteroid3.png");
    asteroidTextures[3].loadTextureStandalone("data/textures/asteroids/asteroid4.png");

    // packer must be after ALL texture loading, remember that in the future please - myself
    RunTexturePacking();

    std::random_device random;
    std::default_random_engine engine{random()};
    std::uniform_int_distribution<int> distribution{0, 3};
    std::uniform_int_distribution<int> asteroidPosition{0, ASTEROID_AREA_SIZE};
    std::uniform_int_distribution<int> asteroidScale{ASTEROID_MIN_SCALE, ASTEROID_MAX_SCALE};
    std::uniform_int_distribution<int> asteroidRotation{0, 360};


    for (auto& n : asteroids) {
        asteroidTextures[distribution(engine)].setSprite(n, distribution(engine));
        n.setScale(float(asteroidScale(engine)) * sf::Vector2f(1, 1));
        n.setRotation(float(asteroidRotation(engine)));
        n.setOrigin(n.getLocalBounds().getSize() / 2.f);
        while (n.getPosition().x < ASTEROID_SAFE_AREA_SIZE and
               n.getPosition().y < ASTEROID_SAFE_AREA_SIZE and
               n.getPosition().y > -ASTEROID_SAFE_AREA_SIZE and
               n.getPosition().y > -ASTEROID_SAFE_AREA_SIZE) {
            n.setPosition(float(asteroidPosition(engine)) - ASTEROID_AREA_SIZE / 2.f, float(asteroidPosition(engine)) - ASTEROID_AREA_SIZE / 2.f);
        }

    }

    // other checks
    if (setting::Resolution().x > 1280 and setting::Resolution().y > 720) {
        setting::editorScale = 1.5f * float(setting::Resolution().x) / 1280.f;
    }

    LoadShipTemplates();
    
    return data;
}