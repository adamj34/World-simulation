#include "organisms/Wolf.hpp"

Wolf::Wolf(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Animal(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("W");
}

Wolf::Wolf(int power, Position position)
    : Wolf(power, 5, 20, 16, position) {
}

Wolf::Wolf(Position position)
    : Wolf(8, position) {
}

Wolf::Wolf()
    : Wolf(Position{ 0, 0 }) {
}