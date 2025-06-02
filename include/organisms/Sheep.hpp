#pragma once

#include "organisms/Animal.hpp"

class Sheep : public Animal {
    public:
        Sheep(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Sheep(int power, Position position);
        explicit Sheep(Position position);
        Sheep();

        std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) override;
        std::optional<std::shared_ptr<Organism>> reproduce() override;

};