#pragma once

#include "Animal.hpp"

class Wolf : public Animal {
    public:
        Wolf(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Wolf(int power, Position position);
        explicit Wolf(Position position);
        Wolf();
};