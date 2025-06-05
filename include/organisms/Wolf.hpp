#pragma once

#include "Animal.hpp"

class Wolf : public Animal {
    public:
        Wolf(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Wolf(int power, Position position);
        explicit Wolf(Position position);
        Wolf();
        Wolf(const Wolf& other);

        std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) override;
        std::shared_ptr<Organism> clone() override;
};