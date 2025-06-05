#include "organisms/Plant.hpp"

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Organism(power, initiative, liveLength, powerToReproduce, position) {
    setSubspecies("P");
}

Plant::Plant(int power, Position position)
    : Organism(power, std::move(position)) {
    setSubspecies("P");
}

Plant::Plant(Position position)
    : Organism(std::move(position)) {
    setSubspecies("P");
}

Plant::Plant()
    : Organism() {
    setSubspecies("P");
}

void Plant::move(const Position& newPosition) {
    // Plants do not move
}

std::optional<std::shared_ptr<Organism>> Plant::reproduce() {
    if (this->canReproduce()) {
        auto offspring { this->clone() };
        setPower(getPower() / 2);
        return offspring;
    }
    return std::nullopt;
}
