#ifndef LOADING_HPP
#define LOADING_HPP

#include <vector>

#include "../classes/part.hpp"
#include "editorShipPart.hpp"

struct DataContainer{

    std::vector <ShipPart*> structurals;


};

DataContainer LoadGame();

inline std::vector <std::vector <ShipPart*>> shipParts;

#endif