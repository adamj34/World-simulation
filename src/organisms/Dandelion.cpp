#include "organisms/Dandelion.hpp"

Dandelion::Dandelion(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Plant(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("D");
}

Dandelion::Dandelion(int power, Position position)
    : Dandelion(power, 0, 6, 2, position) {
}

Dandelion::Dandelion(Position position)
    : Dandelion(0, position) {
}

Dandelion::Dandelion()
    : Dandelion(Position{ 0, 0 }) {
}