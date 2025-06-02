#include "organisms/Dandelion.hpp"

Dandelion::Dandelion(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Plant(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("P");
    setSubspecies("D");
}

Dandelion::Dandelion(int power, Position position)
    : Dandelion(power, 0, 6, 2, position) {
}

Dandelion::Dandelion(Position position)
    : Dandelion(0, position) {
}

Dandelion::Dandelion()
    : Dandelion(Position{ 0, 0 }) {
}

std::optional<std::shared_ptr<Organism>> Dandelion::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // Dandelions do not attack
    return std::nullopt;
}

std::optional<std::shared_ptr<Organism>> Dandelion::reproduce() {
    // Dandelions can reproduce if they have enough power
    if (this->canReproduce()) {
        setPower(getPower() / 2);
        std::shared_ptr<Organism> newDandelion = std::make_shared<Dandelion>();
        return newDandelion;
    }
    return std::nullopt;
}