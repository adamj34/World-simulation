#include "Position.hpp"
#include "Simulator.hpp"
#include "World.hpp"
#include "organisms/Animal.hpp"
#include "organisms/Grass.hpp"
#include "organisms/Organism.hpp"
#include "organisms/OrganismFactory.hpp"
#include "organisms/Plant.hpp"
#include "organisms/Sheep.hpp"
#include "organisms/Toadstool.hpp"
#include "organisms/Wolf.hpp"
#include "serialization.hpp"
#include <iostream>
#include <print>

using namespace std;

int main() {
    World world{ 8, 8 };
    OrganismFactory factory{};

    world.addOrganism(factory.createSheep(Position(0, 0)));
    world.addOrganism(factory.createSheep(Position(1, 1)));
    world.addOrganism(factory.createWolf(Position(2, 2)));
    world.addOrganism(factory.createGrass(Position(3, 3)));
    world.addOrganism(factory.createToadstool(Position(4, 4)));
    world.addOrganism(factory.createDandelion(Position(5, 5)));

    Simulator simulator(world);
    simulator.runSimulation(8);

    return 0;
}