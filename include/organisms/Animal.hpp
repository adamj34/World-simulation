#pragma once
#include "organisms/Organism.hpp"

class Animal : public Organism {
    public:
        Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position);
        Animal(int power, Position position);
        explicit Animal(Position position);
        Animal();
        virtual ~Animal() = default;

        void move(const Position& newPosition) override;

        std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) override = 0;
        std::optional<std::shared_ptr<Organism>> reproduce() override = 0;
};
