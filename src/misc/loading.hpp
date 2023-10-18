#ifndef LOADING_HPP
#define LOADING_HPP

#include <vector>

#include "../classes/part.hpp"

struct DataContainer{

    std::vector <ShipPart> structurals;


};

DataContainer LoadGame();

#endif