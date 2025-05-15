#include "World.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept> 

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
    std::vector<Position> result {};
    for (int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    auto iter = remove_if(result.begin(), result.end(), [this](Position pos) { return !isPositionFree(pos); });
    result.erase(iter, result.end());

    return result;
}

World::World(int worldX, int worldY) {
    setWorldX(worldX);
    setWorldY(worldY);
}

int World::getWorldX() const {
    return m_worldX;
}

void World::setWorldX(int worldX) {
    if (worldX < 0) {
        throw std::invalid_argument("World X dimension cannot be negative");
    }
    m_worldX = worldX;
}

int World::getWorldY() const {
    return m_worldY;
}

void World::setWorldY(int worldY) {
    if (worldY < 0) {
        throw std::invalid_argument("World Y dimension cannot be negative");
    }
    m_worldY = worldY;
}

int World::getTurn() const {
    return m_turn;
}

void World::addOrganism(Organism organism) {
    m_organisms.push_back(std::move(organism)); // avoides making another copy
}

void World::makeTurn() {
    std::vector<Position> newPositions {};
    int numberOfNewPositions { 0 };
    int randomIndex { 0 };

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

void World::writeWorld(std::string fileName) {
    std::fstream my_file;
    my_file.open(fileName, std::ios::out | std::ios::binary);
    if (my_file.is_open()) {
        my_file.write((char*)&this->m_worldX, sizeof(int));
        my_file.write((char*)&this->m_worldY, sizeof(int));
        my_file.write((char*)&this->m_turn, sizeof(int));
        int orgs_size = this->m_organisms.size();
        my_file.write((char*)&orgs_size, sizeof(int));
        for (int i = 0; i < orgs_size; i++) {
            int data;
            data = m_organisms[i].getPower();
            my_file.write((char*)&data, sizeof(int));
            data = m_organisms[i].getPosition().getX();
            my_file.write((char*)&data, sizeof(int));
            data = m_organisms[i].getPosition().getY();
            my_file.write((char*)&data, sizeof(int));
            std::string s_data = m_organisms[i].getSpecies();
            int s_size = s_data.size();
            my_file.write((char*)&s_size, sizeof(int));
            my_file.write(s_data.data(), s_data.size());
        }
        my_file.close();
    }
}

void World::readWorld(std::string fileName) {
    std::fstream my_file;
    my_file.open(fileName, std::ios::in | std::ios::binary);
    if (my_file.is_open()) {
        int result;
        my_file.read((char*)&result, sizeof(int));
        this->m_worldX = (int)result;
        my_file.read((char*)&result, sizeof(int));
        this->m_worldY = (int)result;
        my_file.read((char*)&result, sizeof(int));
        this->m_turn = (int)result;
        my_file.read((char*)&result, sizeof(int));
        int orgs_size = (int)result;
        std::vector<Organism> new_organisms;
        for (int i = 0; i < orgs_size; i++) {
            int power;
            my_file.read((char*)&result, sizeof(int));
            power = (int)result;

            int pos_x;
            my_file.read((char*)&result, sizeof(int));
            pos_x = (int)result;
            int pos_y;
            my_file.read((char*)&result, sizeof(int));
            pos_y = (int)result;
            Position pos{ pos_x, pos_y };

            int s_size;
            my_file.read((char*)&result, sizeof(int));
            s_size = (int)result;

            std::string m_species;
            m_species.resize(s_size);
            my_file.read((char*)&m_species[0], s_size);

            Organism org(power, pos);
            org.setSpecies(m_species);
            new_organisms.push_back(org);
        }
        m_organisms = new_organisms;
        my_file.close();
    }
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
