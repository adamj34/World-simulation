#pragma once

#include "organisms/Plant.hpp"

class Toadstool : public Plant {
    public:
        Toadstool(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Toadstool(int power, Position position);
        Toadstool(Position position);
        Toadstool();
};