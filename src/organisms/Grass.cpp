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

std::optional<std::shared_ptr<Organism>> Grass::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // Grass does not attack
    return std::nullopt;
}

std::optional<std::shared_ptr<Organism>> Grass::reproduce() {
    if (this->canReproduce()) {
        setPower(getPower() / 2);
        std::shared_ptr<Organism> newGrass = std::make_shared<Grass>();
        return newGrass;
    }
    return std::nullopt;
}