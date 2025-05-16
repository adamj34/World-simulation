#include <iostream>
#include <print>
#include "Position.hpp"
#include "organisms/Organism.hpp"
#include "organisms/Plant.hpp"
#include "organisms/Animal.hpp"
#include "organisms/Wolf.hpp"
#include "organisms/Sheep.hpp"
#include "organisms/Grass.hpp"
#include "organisms/Toadstool.hpp"
#include "World.hpp"

using namespace std;

int main()
{
	// Position 
	Position p1;
	Position p2{ 1, 1 };
	Position p3{ 0, 0 };

	//cout << p1.toString() << endl;
	//cout << p2.toString() << endl;
	//cout << p3.toString() << endl;
	//cout << p1.distance(p2) << endl;
	//p2.move(4, 6);
	//cout << p2.toString() << endl;

	// Organism
	//Organism org1;
	//Organism org2{ 10, p2 };

	//cout << org1.toString() << endl;
	//cout << org2.toString() << endl;
	//org1.move(2, 3);
	//cout << org1.toString() << endl;

	// Plant & Animal
	Plant plant{ 3, p3 };
	Animal animal{ 5, p2 };
	Plant plant2;
	Animal animal2;

	cout << plant.toString() << endl;
	cout << animal.toString() << endl;
	cout << plant2.toString() << endl;
	cout << animal2.toString() << endl;
	plant.move(3, 4);
	cout << plant.toString() << endl;
	animal.move(1, 2);
	cout << animal.toString() << endl;
	
	// World test
	World world;
	Position posP1{ 4, 5 };
	Plant plantW1{ 3, posP1 };
	Position posP2{ 5, 4 };
	Plant plantW2{ 3, posP2 };

	Position posW2{ 3, 2 };
	Animal animalW1{ 6, posW2 };
	Position posW3{ 2, 3 };
	Animal animalW2{ 6, posW3 };

	world.addOrganism(plantW1);
	world.addOrganism(plantW2);
	world.addOrganism(animalW1);
	world.addOrganism(animalW2);

	auto positions = world.getVectorOfFreePositionsAround(Position(5, 5));

	for(auto pos: positions)
		cout << pos.toString() << endl;

	// Tura 0
	cout << world.toString() << endl;

	// Tura 1
	world.makeTurn();
	cout << world.toString() << endl;

	// Tura 2
	world.makeTurn();
	cout << world.toString() << endl;

	// world.writeWorld("world.bin");

	// Tura 3
	world.makeTurn();
	cout << world.toString() << endl;

	// // powrot do Tury 2
	// world.readWorld("world.bin");
	// cout << world.toString() << endl;

	// Wolf org1{};
    Sheep org2{};
    // Grass org3{};
    // Toadstool org4{};

	// println("Organism 1: {}", org1.toString());
	// println("Organism 2: {}", org2.toString());
	// println("Organism 3: {}", org3.toString());
	// println("Organism 4: {}", org4.toString());

	return 0;
}