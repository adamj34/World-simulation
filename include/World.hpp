#pragma once

#include "organisms/Organism.hpp"
#include <ctime>
#include <string>
#include <vector>

class World {
    private:
        int m_worldX{ 6 };
        int m_worldY{ 6 };
        int m_turn{ 0 };
        std::vector<Organism> m_organisms{};
        char m_separator{ '.' };

        std::string getOrganismFromPosition(int x, int y);
        bool isPositionOnWorld(int x, int y);
        bool isPositionFree(Position position);

    public:
        World(int worldX, int worldY);
        World() = default;

        int getWorldX() const;
        void setWorldX(int worldX);
        int getWorldY() const;
        void setWorldY(int worldY);

        int getTurn() const;

        void addOrganism(Organism organism);
        std::vector<Position> getVectorOfFreePositionsAround(const Position& position);
        void makeTurn();

        void writeWorld(std::string fileName);
        void readWorld(std::string fileName);

        std::string toString();
};
