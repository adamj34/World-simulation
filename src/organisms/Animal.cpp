#include "organisms/Animal.hpp"

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Organism(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("A");
}

Animal::Animal(Position position)
    : Organism(position) {
    setSpecies("A");
}

Animal::Animal(int power, Position position)
    : Organism(power, position) {
    setSpecies("A");
}

Animal::Animal()
    : Organism() {
    setSpecies("A");
}

void Animal::move(int dx, int dy) {
}
