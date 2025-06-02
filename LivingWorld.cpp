#include "Position.hpp"
#include "World.hpp"
#include "organisms/Animal.hpp"
#include "organisms/Grass.hpp"
#include "organisms/Organism.hpp"
#include "organisms/Plant.hpp"
#include "organisms/Sheep.hpp"
#include "organisms/Toadstool.hpp"
#include "organisms/Wolf.hpp"
#include "Simulator.hpp"
#include "serialization.hpp"
#include <iostream>
#include <print>

using namespace std;

int main() {
	// Create a world with dimensions 6x6
	World world(8, 8);

	// Add some organisms to the world
	world.addOrganism(make_shared<Sheep>(Position(0, 0)));
	world.addOrganism(make_shared<Sheep>(Position(1, 1)));
	world.addOrganism(make_shared<Wolf>(Position(2, 2)));
	world.addOrganism(make_shared<Grass>(Position(3, 3)));
	world.addOrganism(make_shared<Toadstool>(Position(4, 4)));
	world.addOrganism(make_shared<Dandelion>(Position(5, 5)));

	// Run a simulation for 5 turns
	Simulator simulator(world);
	simulator.runSimulation(20);


	return 0;
}