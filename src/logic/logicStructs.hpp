#ifndef LOGIC_STRUCTS_HPP
#define LOGIC_STRUCTS_HPP

#include <cstdint>

struct LogicStage{
    uint8_t type:7;
    bool isBlocking:1;

    LogicStage();
    LogicStage(uint8_t type, bool isBlocking);

    enum {
        editor, game, gameOver
    };
};

#endif