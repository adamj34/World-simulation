#include "organisms/Plant.hpp"

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Organism(power, initiative, liveLength, powerToReproduce, position) {
    setSubspecies("P");
}

Plant::Plant(int power, Position position)
    : Organism(power, position) {
    setSubspecies("P");
}

Plant::Plant(Position position)
    : Organism(position) {
    setSubspecies("P");
}

Plant::Plant()
    : Organism() {
    setSubspecies("P");
}

void Plant::move(const Position& newPosition) {
    // Plants do not move
}
