#pragma once

#include "organisms/Plant.hpp"

class Toadstool : public Plant {
    public:
        Toadstool(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Toadstool(int power, Position position);
        explicit Toadstool(Position position);
        Toadstool();

        std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) override;
        std::optional<std::shared_ptr<Organism>> reproduce() override;
};