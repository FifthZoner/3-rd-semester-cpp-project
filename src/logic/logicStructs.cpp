#include "logicStructs.hpp"

LogicStage::LogicStage(){
    type = 0;
    isBlocking = false;
}
LogicStage::LogicStage(uint8_t type, bool isBlocking){
    this->type = type;
    this->isBlocking = isBlocking;
}