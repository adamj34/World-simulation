#pragma once
#include "organisms/Organism.hpp"

class Plant : public Organism {
    public:
        Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Plant(int power, Position position);
        explicit Plant(Position position);
        Plant();
        virtual ~Plant() = default;

        void move(const Position& newPosition) override;
        std::optional<std::shared_ptr<Organism>> reproduce() override;
        
        std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) override = 0;
        std::shared_ptr<Organism> clone() override = 0;
    };
