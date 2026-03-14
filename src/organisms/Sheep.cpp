#include "organisms/Sheep.hpp"
#include "organisms/SpeciesCodes.hpp"

Sheep::Sheep(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Animal(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies(SpeciesCodes::Animal);
    setSubspecies(SpeciesCodes::Sheep);
}

Sheep::Sheep(int power, Position position)
    : Sheep(power, 3, 10, 6, std::move(position)) {
}

Sheep::Sheep(Position position)
    : Sheep(3, std::move(position)) {
}

Sheep::Sheep()
    : Sheep(Position{ 0, 0 }) {
}

Sheep::Sheep(const Sheep& other)
    : Sheep(3, other.getInitiative(), 10, other.getPowerToReproduce(), other.getPosition()) {
}

std::optional<std::shared_ptr<Organism>> Sheep::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // sheep eats grass and dandelions
    for (const auto& organism : organismsToAttack) {
        if (organism->getSubspecies() == SpeciesCodes::Grass || organism->getSubspecies() == SpeciesCodes::Dandelion) {
            return organism;
        }
    }

    return std::nullopt; 
}

std::shared_ptr<Organism> Sheep::clone() {
    return std::make_shared<Sheep>(*this);
}
