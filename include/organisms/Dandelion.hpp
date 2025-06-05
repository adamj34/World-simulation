#pragma once

#include "organisms/Plant.hpp"

class Dandelion : public Plant {
    public:
        Dandelion(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Dandelion(int power, Position position);
        explicit Dandelion(Position position);
        Dandelion();
        Dandelion(const Dandelion& other);

        std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) override;
        std::shared_ptr<Organism> clone() override;
};