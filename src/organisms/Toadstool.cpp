#include "organisms/Toadstool.hpp"

Toadstool::Toadstool(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Plant(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("P");
    setSubspecies("T");
}

Toadstool::Toadstool(int power, Position position)
    : Toadstool(power, 0, 12, 4, position) {
}

Toadstool::Toadstool(Position position)
    : Toadstool(0, position) {
}

Toadstool::Toadstool()
    : Toadstool(Position{ 0, 0 }) {
}

std::optional<std::shared_ptr<Organism>> Toadstool::attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) {
    // Toadstool kills sheep if they are in the same position
    for (const auto& organism : organismsToAttack) {
        if (organism->getSubspecies() == "S") {
            return organism;
        }
    }
    return std::nullopt; 
}

std::optional<std::shared_ptr<Organism>> Toadstool::reproduce() {
    if (this->canReproduce()) {
        setPower(getPower() / 2);
        std::shared_ptr<Organism> newToadstool = std::make_shared<Toadstool>();
        return newToadstool;
    }
    return std::nullopt;
}