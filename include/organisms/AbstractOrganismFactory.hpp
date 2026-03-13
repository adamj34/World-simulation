#pragma once

#include "organisms/Organism.hpp"
#include <memory>

class AbstractOrganismFactory {
    public:
        virtual ~AbstractOrganismFactory() = default;

        virtual std::shared_ptr<Organism> createWolf(Position position) const = 0;
        virtual std::shared_ptr<Organism> createSheep(Position position) const = 0;
        virtual std::shared_ptr<Organism> createGrass(Position position) const = 0;
        virtual std::shared_ptr<Organism> createDandelion(Position position) const = 0;
        virtual std::shared_ptr<Organism> createToadstool(Position position) const = 0;
};