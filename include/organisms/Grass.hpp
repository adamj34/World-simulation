#pragma once

#include "organisms/Plant.hpp"

class Grass : public Plant {
    public:
        Grass(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Grass(int power, Position position);
        explicit Grass(Position position);
        Grass();
        Grass(const Grass& other);

        std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) override;
        std::shared_ptr<Organism> clone() override;
};