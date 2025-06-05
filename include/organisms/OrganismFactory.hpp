#pragma once

#include "organisms/AbstractOrganismFactory.hpp"
#include "organisms/Organism.hpp"
#include "Position.hpp"
#include <memory>

class OrganismFactory : public AbstractOrganismFactory {
    public:
        std::shared_ptr<Organism> createWolf(Position position = Position{}) const override;
        std::shared_ptr<Organism> createSheep(Position position = Position{}) const override;
        std::shared_ptr<Organism> createGrass(Position position = Position{}) const override;
        std::shared_ptr<Organism> createDandelion(Position position = Position{})const override;
        std::shared_ptr<Organism> createToadstool(Position position = Position{}) const override;

        virtual ~OrganismFactory() = default;
};