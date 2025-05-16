#include "World.hpp"
#include "validators.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

std::string World::getOrganismFromPosition(int x, int y) {
    for (const Organism& org : m_organisms) {
        if (org.getPosition().getX() == x && org.getPosition().getY() == y) {
            return org.getSpecies();
        }
    }
    return "";
}

bool World::isPositionOnWorld(int x, int y) {
    return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
    return getOrganismFromPosition(position.getX(), position.getY()).empty();
}

std::vector<Position> World::getVectorOfFreePositionsAround(const Position& position) {
    int pos_x = position.getX(), pos_y = position.getY();
    std::vector<Position> result{};
    for (int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    auto iter = remove_if(result.begin(), result.end(), [this](Position pos) { return !isPositionFree(pos); });
    result.erase(iter, result.end());

    return result;
}

World::World(int worldX, int worldY, int startWorldX, int startWorldY)
    : m_worldX{ worldX }
    , m_worldY{ worldY }
    , m_startWorldX{ startWorldX }
    , m_startWorldY{ startWorldY } {
    validators::validateDimension(m_startWorldX, m_worldX);
    validators::validateDimension(m_startWorldY, m_worldY);
}

int World::getStartWorldX() const {
    return m_startWorldX;
}
void World::setStartWorldX(int startWorldX) {
    validators::validateValueNotNegative(startWorldX);
    m_startWorldX = startWorldX;
}

int World::getStartWorldY() const {
    return m_startWorldY;
}
void World::setStartWorldY(int startWorldY) {
    validators::validateValueNotNegative(startWorldY);
    m_startWorldY = startWorldY;
}

int World::getWorldX() const {
    return m_worldX;
}
void World::setWorldX(int worldX) {
    validators::validateDimension(m_startWorldX, worldX);
    m_worldX = worldX;
}

int World::getWorldY() const {
    return m_worldY;
}
void World::setWorldY(int worldY) {
    validators::validateDimension(m_startWorldY, worldY);
    m_worldY = worldY;
}

int World::getTurn() const {
    return m_turn;
}

const std::vector<Organism>& World::getOrganisms() const {
    return m_organisms;
}

void World::addOrganism(Organism organism) {
    auto insertPos = std::find_if(m_organisms.begin(), m_organisms.end(), [&organism](const Organism& vec_org) {
        return vec_org.getInitiative() < organism.getInitiative();
    });

    m_organisms.insert(insertPos, std::move(organism));
}

void World::makeTurn() {
    std::vector<Position> newPositions{};
    int numberOfNewPositions{ 0 };
    int randomIndex{ 0 };

    srand(time(0));
    for (auto& org : m_organisms) {
        newPositions = getVectorOfFreePositionsAround(org.getPosition());
        numberOfNewPositions = newPositions.size();
        if (numberOfNewPositions > 0) {
            randomIndex = rand() % numberOfNewPositions;
            org.setPosition(newPositions[randomIndex]);
        }
    }
    m_turn++;
}

std::string World::toString() {
    std::string result{ "\nturn: " + std::to_string(getTurn()) + "\n" };
    std::string spec{};

    for (int wY = 0; wY < getWorldY(); ++wY) {
        for (int wX = 0; wX < getWorldX(); ++wX) {
            spec = getOrganismFromPosition(wX, wY);
            if (spec != "")
                result += spec;
            else
                result += m_separator;
        };
        result += "\n";
    }
    return result;
}
