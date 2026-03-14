#include "World.hpp"
#include "Position.hpp"
#include "organisms/Organism.hpp"
#include "organisms/SpeciesCodes.hpp"
#include "validators.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::shared_ptr<Organism>> World::getOrganismsFromPosition(const Position& positionToCheck) {

    std::vector<std::shared_ptr<Organism>> organismsAtPosition{};
    for (const auto& organism : m_organisms) {
        if (organism->getPosition().getX() == positionToCheck.getX() &&
            organism->getPosition().getY() == positionToCheck.getY()) {
            organismsAtPosition.push_back(organism);
        }
    }

    return organismsAtPosition;
}

bool World::isPositionOnWorld(int x, int y) {
    return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(const Position& position) {
    return getOrganismsFromPosition(position).empty();
}

bool World::isPositionAnimalFree(const Position& position) {
    auto organismsAtPosition = getOrganismsFromPosition(position);
    if (!organismsAtPosition.empty()) {
        for (const auto& organism : organismsAtPosition) {
            if (organism->getSpecies() == SpeciesCodes::Animal) {
                return false;
            }
        }
    }
    return true;
}

std::vector<Position> World::getPositionsAround(const std::shared_ptr<Organism>& organism) {
    auto organismPosition = organism->getPosition();
    int pos_x = organismPosition.getX();
    int pos_y = organismPosition.getY();
    std::vector<Position> result{};
    for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
            if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
        }
    }
    return result;
}

std::vector<Position> World::getFreePositionsAround(std::vector<Position> positionsAround) {
    auto iter = std::remove_if(positionsAround.begin(), positionsAround.end(),
                          [this](Position pos) { return !isPositionFree(pos); });
    positionsAround.erase(iter, positionsAround.end());

    return positionsAround;
}

std::vector<Position> World::getAnimalFreePositionsAround(std::vector<Position> positionsAround) {

    auto iter = std::remove_if(positionsAround.begin(), positionsAround.end(),
                          [this](Position pos) { return !isPositionAnimalFree(pos); });
    positionsAround.erase(iter, positionsAround.end());

    return positionsAround;
}

std::vector<Position> World::getValidPositionsAround(const std::shared_ptr<Organism>& organism) {
    auto positionsAround = getPositionsAround(organism);
    if (organism->getSpecies() == SpeciesCodes::Animal) {
        return getAnimalFreePositionsAround(positionsAround);
    } else {
        return getFreePositionsAround(positionsAround);
    }
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

const std::vector<std::shared_ptr<Organism>>& World::getOrganisms() const {
    return m_organisms;
}
void World::setOrganisms(const std::vector<std::shared_ptr<Organism>>& organisms) {
    m_organisms = organisms;
}

void World::addOrganism(std::shared_ptr<Organism> organism) {
    auto insertPos =
        std::find_if(m_organisms.begin(), m_organisms.end(), [&](const std::shared_ptr<Organism>& vec_org) {
            return vec_org->getInitiative() < organism->getInitiative();
        });

    m_organisms.insert(insertPos, organism);
}

bool World::isOrganismDead(const std::shared_ptr<Organism>& organism) {
    return organism->getLiveLength() <= 0 || organism->getLineageInfo().deathTurn != -1;
}

void World::removeDeadOrganisms() {
    // Removes all elements satisfying specific criteria from the range [first, last) and returns a past-the-end iterator for the new end of the range.
    auto iter = std::remove_if(m_organisms.begin(), m_organisms.end(),
                               [this](const std::shared_ptr<Organism>& org) { return isOrganismDead(org); });
    // Erases the elements in the range [first, last) from the container.
    m_organisms.erase(iter, m_organisms.end());
}

void World::markOrganismAsDead(const std::shared_ptr<Organism>& organism, int deathTurn) {
    organism->setDeathTurn(deathTurn);
}

bool World::organismCanPlayTurn(const std::shared_ptr<Organism>& organism) const {
    return organism->isAlive();
}

void World::increaseOrganismsPowerBy(int increment) {
    for (const auto& organism : m_organisms) {
        organism->setPower(organism->getPower() + increment);
    }
}

void World::decreaseOrganismsLiveLengthBy(int decrement) {
    for (const auto& organism : m_organisms) {
        organism->setLiveLength(organism->getLiveLength() - decrement);
    }
}

std::string World::toString() {
    std::string result{};
    std::vector<std::shared_ptr<Organism>> spec;

    for (int wY = 0; wY < getWorldY(); ++wY) {
        for (int wX = 0; wX < getWorldX(); ++wX) {
            spec = getOrganismsFromPosition(Position(wX, wY));
            if (!spec.empty()) {
                result += speciesCodeToSymbol(spec.front()->getSubspecies());
            } else {
                result += m_separator;
            }
        };
        result += "\n";
    }
    return result;
}

bool World::operator==(const World& other) const {
    if (m_worldX != other.m_worldX || m_worldY != other.m_worldY || m_startWorldX != other.m_startWorldX ||
        m_startWorldY != other.m_startWorldY || m_separator != other.m_separator ||
        m_organisms.size() != other.m_organisms.size()) {
        return false;
    }

    for (int i = 0; i < m_organisms.size(); ++i) {
        if (typeid(*m_organisms[i]) != typeid(*other.m_organisms[i])) {
            return false;
        }

        if (!(*m_organisms[i] == *other.m_organisms[i])) {
            return false;
        }
    }

    return true;
}
