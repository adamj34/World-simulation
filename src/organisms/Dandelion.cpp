#include "organisms/Dandelion.hpp"
#include "organisms/SpeciesCodes.hpp"

Dandelion::Dandelion(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Plant(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies(SpeciesCodes::Plant);
    setSubspecies(SpeciesCodes::Dandelion);
}

Dandelion::Dandelion(int power, Position position)
    : Dandelion(power,
                species_defaults::dandelion.initiative,
                species_defaults::dandelion.liveLength,
                species_defaults::dandelion.powerToReproduce,
                position) {
}

Dandelion::Dandelion(Position position)
    : Dandelion(species_defaults::dandelion.power, position) {
}

Dandelion::Dandelion()
    : Dandelion(Position{ 0, 0 }) {
}

Dandelion::Dandelion(const Dandelion& other)
    : Dandelion(species_defaults::dandelion.power,
                other.getInitiative(),
                species_defaults::dandelion.liveLength,
                other.getPowerToReproduce(),
                other.getPosition()) {
}

std::optional<std::shared_ptr<Organism>> Dandelion::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // Dandelions do not attack
    return std::nullopt;
}

std::shared_ptr<Organism> Dandelion::clone() {
    return std::make_shared<Dandelion>(*this);
}