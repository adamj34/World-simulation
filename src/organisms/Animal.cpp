#include "organisms/Animal.hpp"

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Organism(power, initiative, liveLength, powerToReproduce, position) {
    setSubspecies("A");
}

Animal::Animal(Position position)
    : Organism(std::move(position)) {
    setSubspecies("A");
}

Animal::Animal(int power, Position position)
    : Organism(power, std::move(position)) {
    setSubspecies("A");
}

Animal::Animal()
    : Organism() {
    setSubspecies("A");
}

void Animal::move(const Position& newPosition) {
    setPosition(newPosition);
}

std::optional<std::shared_ptr<Organism>> Animal::reproduce() {
    if (this->canReproduce()) {
        auto offspring { this->clone() };
        setPower(getPower() / 2);
        return offspring;
    }
    return std::nullopt;
}