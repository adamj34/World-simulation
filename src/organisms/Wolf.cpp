#include "organisms/Wolf.hpp"

Wolf::Wolf(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Animal(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("A");
    setSubspecies("W");
}

Wolf::Wolf(int power, Position position)
    : Wolf(power, 5, 20, 16, position) {
}

Wolf::Wolf(Position position)
    : Wolf(8, position) {
}

Wolf::Wolf()
    : Wolf(Position{ 0, 0 }) {
}

std::optional<std::shared_ptr<Organism>> Wolf::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // Wolves attack only other animals
    for (const auto& organism : organismsToAttack) {
        if (organism->getSpecies() == "A" && organism->getSubspecies() != this->getSubspecies()) {
            if (this->getPower() > organism->getPower()) {
                return organism;
            }
        }
    }
    return std::nullopt; 
}

std::optional<std::shared_ptr<Organism>> Wolf::reproduce() {
    // Wolves can reproduce if they have enough power
    if (this->canReproduce()) {
        setPower(getPower() / 2);
        std::shared_ptr<Organism> newWolf = std::make_shared<Wolf>();
        return newWolf;
    }
    return std::nullopt;
}