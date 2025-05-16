#pragma once

#include "organisms/Plant.hpp"

class Grass : public Plant {
    public:
        Grass(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Grass(int power, Position position);
        explicit Grass(Position position);
        Grass();
};