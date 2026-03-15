#pragma once

#include "Position.hpp"
#include "organisms/Organism.hpp"
#include <memory>
#include <string>
#include <vector>

class ISimulationWorld {
    public:
        virtual ~ISimulationWorld() = default;

        virtual const std::vector<std::shared_ptr<Organism>>& getOrganisms() const = 0;
        virtual std::vector<std::shared_ptr<Organism>> getOrganismsFromPosition(const Position& positionToCheck) = 0;
        virtual std::vector<Position> getPositionsAround(const std::shared_ptr<Organism>& organism) = 0;
        virtual std::vector<Position> getValidPositionsAround(const std::shared_ptr<Organism>& organism) = 0;

        virtual bool organismCanPlayTurn(const std::shared_ptr<Organism>& organism) const = 0;
        virtual void markOrganismAsDead(const std::shared_ptr<Organism>& organism, int deathTurn) = 0;
        virtual void addOrganism(std::shared_ptr<Organism> organism) = 0;

        virtual void increaseOrganismsPowerBy(int increment) = 0;
        virtual void decreaseOrganismsLiveLengthBy(int decrement) = 0;
        virtual void removeDeadOrganisms() = 0;

        virtual std::string toString() = 0;
};
