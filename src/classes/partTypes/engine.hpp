#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_ENGINE_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_ENGINE_HPP

#include "../part.hpp"

class ShipEngine : public ShipPart {
private:
    uint16_t thrust = 0;
    uint16_t drain = 0;
public:
    void create(std::string path) override;
    ShipEngine(std::string path);
    uint8_t type() override;
};

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_ENGINE_HPP
