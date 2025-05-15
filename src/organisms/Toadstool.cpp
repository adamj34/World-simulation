#include "organisms/Toadstool.hpp"

Toadstool::Toadstool(int power, int initiative, int liveLength, int powerToReproduce, Position position)
    : Plant(power, initiative, liveLength, powerToReproduce, position) {
    setSpecies("T");
}

Toadstool::Toadstool(int power, Position position)
    : Toadstool(power, 0, 12, 4, position) {
}

Toadstool::Toadstool(Position position)
    : Toadstool(0, position) {
}

Toadstool::Toadstool()
    : Toadstool(Position{ 0, 0 }) {
}