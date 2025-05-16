#pragma once
#include "organisms/Organism.hpp"

class Animal : public Organism {
    public:
        Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Animal(int power, Position position);
        explicit Animal(Position position);
        Animal();

        void move(int dx, int dy) override;
};
