#include "organisms/Organism.hpp"
#include "validators.hpp"
#include <string>

Organism::Organism(Position position)
    : m_position{ position } {
}

Organism::Organism(int power, Position position)
    : m_power{ power }
    , m_position{ position } {
    validators::validateValueNotNegative(power, "Power");
}

Organism::Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : m_power{ power }
    , m_initiative{ initiative }
    , m_liveLength{ liveLength }
    , m_powerToReproduce{ powerToReproduce }
    , m_position{ position } {
    validators::validateValueNotNegative(power, "Power");
    validators::validateValueNotNegative(initiative, "Initiative");
    validators::validateValueNotNegative(liveLength, "Live length");
    validators::validateValueNotNegative(powerToReproduce, "Power to reproduce");
}

int Organism::getPower() const {
    return m_power;
}
void Organism::setPower(int power) {
    validators::validateValueNotNegative(power, "Power");
    m_power = power;
}

int Organism::getInitiative() const {
    return m_initiative;
}
void Organism::setInitiative(int initiative) {
    validators::validateValueNotNegative(initiative, "Initiative");
    m_initiative = initiative;
}

int Organism::getLiveLength() const {
    return m_liveLength;
}
void Organism::setLiveLength(int liveLength) {
    validators::validateValueNotNegative(liveLength, "Live length");
    m_liveLength = liveLength;
}

int Organism::getPowerToReproduce() const {
    return m_powerToReproduce;
}
void Organism::setPowerToReproduce(int powerToReproduce) {
    validators::validateValueNotNegative(powerToReproduce, "Power to reproduce");
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
    return "{ m_species: " + getSpecies() + ", power: " + std::to_string(getPower()) +
           ", initiative: " + std::to_string(getInitiative()) + ", liveLength: " + std::to_string(getLiveLength()) +
           ", powerToReproduce: " + std::to_string(getPowerToReproduce()) + ", position: " + getPosition().toString() +
           "}";
}

// Test function to change x coordinate
void Organism::test_change_x(int x) {
    m_position.setX(x);
}