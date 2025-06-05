#pragma once

#include "organisms/Organism.hpp"
#include <memory>

class AbstractOrganismFactory {
    public:
        virtual ~AbstractOrganismFactory() = default;

        virtual std::shared_ptr<Organism> createWolf(Position positon) const = 0;
        virtual std::shared_ptr<Organism> createSheep(Position positon) const = 0;
        virtual std::shared_ptr<Organism> createGrass(Position positon) const = 0;
        virtual std::shared_ptr<Organism> createDandelion(Position positon) const = 0;
        virtual std::shared_ptr<Organism> createToadstool(Position positon) const = 0;
};