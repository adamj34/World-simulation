#include "organisms/Sheep.hpp"

Sheep::Sheep(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Animal(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("S");
}

Sheep::Sheep(int power, Position position)
    : Sheep(power, 3, 10, 6, position) {
}

Sheep::Sheep(Position position)
    : Sheep(3, position) {
}

Sheep::Sheep()
    : Sheep(Position{ 0, 0 }) {
}