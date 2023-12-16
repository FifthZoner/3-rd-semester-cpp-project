#ifndef INC_3_RD_SEMESTER_CPP_PROJECT_CONTROL_HPP
#define INC_3_RD_SEMESTER_CPP_PROJECT_CONTROL_HPP

#include "../part.hpp"

class ShipControl : public ShipPart {
public:
    void create(std::string path) override;
    ShipControl(std::string path);
};
#endif
