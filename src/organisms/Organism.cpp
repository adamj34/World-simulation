#include "organisms/Organism.hpp"
#include "validators.hpp"
#include <print>
#include <string>

Organism::Organism(Position position)
    : m_position{ std::move(position) } {
}

Organism::Organism(int power, Position position)
    : m_power{ power }
    , m_position{ std::move(position) } {
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

bool Organism::operator==(const Organism& other) const {
    return m_power == other.m_power && m_initiative == other.m_initiative && m_liveLength == other.m_liveLength &&
           m_powerToReproduce == other.m_powerToReproduce && m_position == other.m_position &&
           m_species == other.m_species;
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

LineageInfo Organism::getLineageInfo() const {
    return m_lineageInfo;
}
void Organism::setLineageInfo(LineageInfo lineageInfo) {
    m_lineageInfo = lineageInfo;
}

std::shared_ptr<Organism> Organism::getParent() const {
    return m_lineageInfo.parent;
}

int Organism::getBirthTurn() const {
    return m_lineageInfo.birthTurn;
}

int Organism::getDeathTurn() const {
    return m_lineageInfo.deathTurn;
}

std::string Organism::getSpecies() const {
    return m_species;
}
void Organism::setSpecies(std::string spec) {
    m_species = spec;
}

std::string Organism::getSubspecies() const {
    return m_subspecies;
}
void Organism::setSubspecies(std::string subspec) {
    m_subspecies = subspec;
}

bool Organism::canReproduce() const {
    return m_power >= m_powerToReproduce;
}

bool Organism::isAlive() const {
    return getDeathTurn() == -1 && m_liveLength > 0;
}

void Organism::setDeathTurn(int deathTurn) {
    validators::validateValueNotNegative(deathTurn, "Death turn");
    m_lineageInfo.deathTurn = deathTurn;
}

std::string Organism::toString() const {
    return "{ m_species: " + getSpecies() + ", power: " + std::to_string(getPower()) +
           ", initiative: " + std::to_string(getInitiative()) + ", liveLength: " + std::to_string(getLiveLength()) +
           ", powerToReproduce: " + std::to_string(getPowerToReproduce()) + ", position: " + getPosition().toString() +
           "}";
}

