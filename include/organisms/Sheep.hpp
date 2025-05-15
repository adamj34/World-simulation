#pragma once

#include "organisms/Animal.hpp"

class Sheep : public Animal {
    public:
        Sheep(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Sheep(int power, Position position);
        Sheep(Position position);
        Sheep();
};