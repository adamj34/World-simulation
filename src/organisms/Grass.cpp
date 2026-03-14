#include "organisms/Grass.hpp"
#include "organisms/SpeciesCodes.hpp"

Grass::Grass(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Plant(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies(SpeciesCodes::Plant);
    setSubspecies(SpeciesCodes::Grass);
}

Grass::Grass(int power, Position position)
    : Grass(power,
            species_defaults::grass.initiative,
            species_defaults::grass.liveLength,
            species_defaults::grass.powerToReproduce,
            position) {
}

Grass::Grass(Position position)
    : Grass(species_defaults::grass.power, position) {
}

Grass::Grass()
    : Grass(Position{ 0, 0 }) {
}

Grass::Grass(const Grass& other)
    : Grass(species_defaults::grass.power,
            other.getInitiative(),
            species_defaults::grass.liveLength,
            other.getPowerToReproduce(),
            other.getPosition()) {
}

std::optional<std::shared_ptr<Organism>> Grass::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // Grass does not attack
    return std::nullopt;
}

std::shared_ptr<Organism> Grass::clone() {
    return std::make_shared<Grass>(*this);
}