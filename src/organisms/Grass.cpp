#include "organisms/Grass.hpp"

Grass::Grass(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Plant(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("P");
    setSubspecies("G");
}

Grass::Grass(int power, Position position)
    : Grass(power, 0, 6, 3, position) {
}

Grass::Grass(Position position)
    : Grass(0, position) {
}

Grass::Grass()
    : Grass(Position{ 0, 0 }) {
}

Grass::Grass(const Grass& other)
    : Grass(0, other.getInitiative(), 6, other.getPowerToReproduce(), other.getPosition()) {
}

std::optional<std::shared_ptr<Organism>> Grass::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // Grass does not attack
    return std::nullopt;
}

std::shared_ptr<Organism> Grass::clone() {
    return std::make_shared<Grass>(*this);
}