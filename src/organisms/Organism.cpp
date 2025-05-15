#include "organisms/Organism.hpp"
#include <stdexcept>
#include <string>

Organism::Organism(Position position) 
    : Organism() {
        setPosition(position);
    }
    
Organism::Organism(int power, Position position)
    : Organism(position) {
        setPower(power);
    }

Organism::Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position) 
    : Organism(power, position) {
        setInitiative(initiative);
        setLiveLength(liveLength);
        setPowerToReproduce(powerToReproduce);
    }

int Organism::getPower() const {
    return m_power;
}
void Organism::setPower(int power) {
    if (power < 0) {
        throw std::invalid_argument("Power cannot be negative");
    }
    m_power = power;
}

int Organism::getInitiative() const {
    return 0;
}
void Organism::setInitiative(int initiative) {
    m_initiative = initiative;
}

int Organism::getLiveLength() const {
    return m_liveLength;
}
void Organism::setLiveLength(int liveLength) {
    if (liveLength < 0) {
        throw std::invalid_argument("Live length cannot be negative");
    }
    m_liveLength = liveLength;
}

int Organism::getPowerToReproduce() const {
    return m_powerToReproduce;
}
void Organism::setPowerToReproduce(int powerToReproduce) {
    if (powerToReproduce < 0) {
        throw std::invalid_argument("Power to reproduce cannot be negative");
    }
    m_powerToReproduce = powerToReproduce;
}

Position Organism::getPosition() const {
    return m_position;
}
void Organism::setPosition(Position position) {
    m_position = position;
}

std::string Organism::getSpecies() const {
    return m_species;
}
void Organism::setSpecies(std::string spec) {
    m_species = spec;
}

void Organism::move(int dx, int dy) {
    m_position.move(dx, dy);
}

std::string Organism::toString() const {
    return "{ m_species: " + getSpecies() +
           ", power: " + std::to_string(getPower()) +
           ", initiative: " + std::to_string(getInitiative()) +
           ", liveLength: " + std::to_string(getLiveLength()) +
           ", powerToReproduce: " + std::to_string(getPowerToReproduce()) +
           ", position: " + getPosition().toString() + "}";
}

// Test function to change x coordinate
void Organism::test_change_x(int x) {
    m_position.setX(x);
}