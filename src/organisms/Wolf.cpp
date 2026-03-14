#include "organisms/Wolf.hpp"
#include "organisms/SpeciesCodes.hpp"

Wolf::Wolf(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Animal(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies(SpeciesCodes::Animal);
    setSubspecies(SpeciesCodes::Wolf);
}

Wolf::Wolf(int power, Position position)
    : Wolf(power, 5, 20, 16, std::move(position)) {
}

Wolf::Wolf(Position position)
    : Wolf(8, std::move(position)) {
}

Wolf::Wolf()
    : Wolf(Position{ 0, 0 }) {
}

Wolf::Wolf(const Wolf& other)
    : Wolf(8, other.getInitiative(), 20, other.getPowerToReproduce(), other.getPosition()) {
}

std::optional<std::shared_ptr<Organism>> Wolf::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // Wolves attack only other animals
    for (const auto& organism : organismsToAttack) {
        if (organism->getSpecies() == SpeciesCodes::Animal && organism->getSubspecies() != this->getSubspecies()) {
            if (this->getPower() > organism->getPower()) {
                return organism;
            }
        }
    }
    return std::nullopt; 
}

std::shared_ptr<Organism> Wolf::clone() {
    return std::make_shared<Wolf>(*this);
}
