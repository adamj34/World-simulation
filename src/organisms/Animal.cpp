#include "organisms/Animal.hpp"

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Organism(power, initiative, liveLength, powerToReproduce, position) {
    setSubspecies("A");
}

Animal::Animal(Position position)
    : Organism(position) {
    setSubspecies("A");
}

Animal::Animal(int power, Position position)
    : Organism(power, position) {
    setSubspecies("A");
}

Animal::Animal()
    : Organism() {
    setSubspecies("A");
}

void Animal::move(const Position& newPosition) {
    // Position currentPosition = getPosition();
    // currentPosition.move(dx, dy);
    // setPosition(currentPosition);
    setPosition(newPosition);
}
