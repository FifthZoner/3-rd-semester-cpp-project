#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_REACTOR_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_REACTOR_HPP

#include "../part.hpp"

class ShipReactor : public ShipPart {
private:
    uint16_t power = 0;
public:
    uint16_t getPower() const;

public:
    void create(std::string path) override;
    ShipReactor(std::string path);
    uint8_t type() override;
};

#endif //INC_3_RD_SEMESTER_CPP_PROJECT_REACTOR_HPP
