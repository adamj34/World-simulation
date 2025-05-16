#pragma once
#include "organisms/Organism.hpp"

class Plant : public Organism {
    public:
        Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Plant(int power, Position position);
        explicit Plant(Position position);
        Plant();

        void move(int dx, int dy) override;
};
