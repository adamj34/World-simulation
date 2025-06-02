#include "organisms/Sheep.hpp"

Sheep::Sheep(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Animal(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("A");
    setSubspecies("S");
}

Sheep::Sheep(int power, Position position)
    : Sheep(power, 3, 10, 6, position) {
}

Sheep::Sheep(Position position)
    : Sheep(3, position) {
}

Sheep::Sheep()
    : Sheep(Position{ 0, 0 }) {
}

std::optional<std::shared_ptr<Organism>> Sheep::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // sheep eats grass and dandelions
    for (const auto& organism : organismsToAttack) {
        if (organism->getSubspecies() == "G" || organism->getSubspecies() == "D") {
            return organism;
        }
    }

    return std::nullopt; 
}

std::optional<std::shared_ptr<Organism>> Sheep::reproduce() {
    // Sheep can reproduce if they have enough power
    if (this->canReproduce()) {
        setPower(getPower() / 2);
        std::shared_ptr<Organism> newSheep = std::make_shared<Sheep>();
        return newSheep;
    }
    return std::nullopt;
}