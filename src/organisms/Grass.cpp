#include "organisms/Grass.hpp"

Grass::Grass(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Plant(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("G");
}

Grass::Grass(int power, Position position)
    : Grass(power, 0, 6, 3, position) {
}

Grass::Grass(Position position)
    : Grass(0, position) {
}

Grass::Grass()
    : Grass(Position{0, 0}) {
}