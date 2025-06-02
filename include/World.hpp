#pragma once

#include "organisms/Organism.hpp"
#include <ctime>
#include <random>
#include <string>
#include <vector>

class World {
    private:
        int m_worldX{ 6 };
        int m_worldY{ 6 };
        int m_startWorldX{ 0 };
        int m_startWorldY{ 0 };
        std::vector<std::shared_ptr<Organism>> m_organisms{};
        char m_separator{ '.' };

        bool isPositionOnWorld(int x, int y);
        bool isPositionFree(const Position& position);
        bool isPositionAnimalFree(const Position& position);
        std::vector<Position> getFreePositionsAround(std::vector<Position> positionsAround);
        std::vector<Position> getAnimalFreePositionsAround(std::vector<Position> positionsAround);

        bool isOrganismDead(const std::shared_ptr<Organism>& organism);

    public:
        World(int worldX, int worldY, int startWorldX = 0, int startWorldY = 0);
        World() = default;

        bool operator==(const World& other) const;

        int getStartWorldX() const;
        void setStartWorldX(int startWorldX);
        int getStartWorldY() const;
        void setStartWorldY(int startWorldY);
        int getWorldX() const;
        void setWorldX(int worldX);
        int getWorldY() const;
        void setWorldY(int worldY);

        const std::vector<std::shared_ptr<Organism>>& getOrganisms() const;
        void setOrganisms(const std::vector<std::shared_ptr<Organism>>& organisms);

        void markOrganismAsDead(std::shared_ptr<Organism>& organism, int deathTurn);
        void addOrganism(std::shared_ptr<Organism> organism);
        std::vector<std::shared_ptr<Organism>> getOrganismsFromPosition(const Position& positionToCheck);
        std::vector<Position> getPositionsAround(const std::shared_ptr<Organism>& organism);
        std::vector<Position> getValidPositionsAround(const std::shared_ptr<Organism>& organism);
        void removeDeadOrganisms();

        std::string toString();
};
