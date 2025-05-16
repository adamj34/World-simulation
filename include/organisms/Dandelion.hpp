#pragma once

#include "organisms/Plant.hpp"

class Dandelion : public Plant {
    public:
        Dandelion(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Dandelion(int power, Position position);
        explicit Dandelion(Position position);
        Dandelion();
};