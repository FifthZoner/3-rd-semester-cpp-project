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

std::vector <std::vector <ShipPart*>> shipParts;

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

std::array <Texturable, 4> asteroidTextures;

#define ASTEROID_SAFE_AREA_SIZE 800
#define ASTEROID_AREA_SIZE 5000
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
    
    return data;
}