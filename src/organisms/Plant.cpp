#include "organisms/Plant.hpp"

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Organism(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("P");
}

Plant::Plant(int power, Position position)
    : Organism(power, position) {
    setSpecies("P");
}

Plant::Plant(Position position)
    : Organism(position) {
    setSpecies("P");
}

Plant::Plant()
    : Organism() {
    setSpecies("P");
}

void Plant::move(int dx, int dy) {
    Organism::move(0, 0);
}
