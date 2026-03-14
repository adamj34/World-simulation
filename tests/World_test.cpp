#include "Position.hpp"
#include "World.hpp"
#include "organisms/Grass.hpp"
#include "organisms/OrganismFactory.hpp"
#include "organisms/Sheep.hpp"
#include "organisms/Toadstool.hpp"
#include "organisms/Wolf.hpp"
#include "organisms/OrganismFactory.hpp"
#include <catch2/catch_test_macros.hpp>
#include <print>

TEST_CASE("Negative values for world dimensions are not allowed", "[World]") {
    SECTION("Negative X dimension throws invalid_argument when constructing World") {
        REQUIRE_THROWS_AS(World(-1, 5), std::invalid_argument);
    }

    SECTION("Negative Y dimension throws invalid_argument when constructing World") {
        REQUIRE_THROWS_AS(World(5, -1), std::invalid_argument);
    }

    SECTION("Negative X dimension throws invalid_argument when setting World X") {
        World world{};
        REQUIRE_THROWS_AS(world.setWorldX(-1), std::invalid_argument);
    }

    SECTION("Negative Y dimension throws invalid_argument when setting World Y") {
        World world{};
        REQUIRE_THROWS_AS(world.setWorldY(-1), std::invalid_argument);
    }
}

TEST_CASE("New organisms are added to the world in sorted order, according to their initiative", "[World]") {
    World world{};
    OrganismFactory factory{};

    auto org1 = factory.createWolf();
    auto org2 = factory.createSheep();
    auto org3 = factory.createGrass();
    auto org4 = factory.createToadstool();
    auto org5 = factory.createWolf();

    world.addOrganism(org2);
    world.addOrganism(org1);
    world.addOrganism(org4);
    world.addOrganism(org3);
    world.addOrganism(org5);

    REQUIRE(world.getOrganisms()[0]->getSubspecies() == "W");
    REQUIRE(world.getOrganisms()[1]->getSubspecies() == "W");
    REQUIRE(world.getOrganisms()[2]->getSubspecies() == "S");
    REQUIRE(world.getOrganisms()[3]->getSubspecies() == "T");
    REQUIRE(world.getOrganisms()[4]->getSubspecies() == "G");
}

TEST_CASE("Dead organisms are removed from the world", "[World]") {
    World world{};
    OrganismFactory factory{};

    auto org1 = factory.createWolf();
    auto org2 = factory.createSheep();
    auto org3 = factory.createGrass();

    world.addOrganism(org1);
    world.addOrganism(org2);
    world.addOrganism(org3);

    SECTION("Killed organism is removed") {
        world.markOrganismAsDead(org1, 9);
        world.removeDeadOrganisms();

        REQUIRE(world.getOrganisms().size() == 2);
        REQUIRE(world.getOrganisms()[0]->getSubspecies() == "S");
        REQUIRE(world.getOrganisms()[1]->getSubspecies() == "G");
    }

    SECTION("Organism with live length 0 is removed") {
        org2->setLiveLength(0);
        world.removeDeadOrganisms();

        REQUIRE(world.getOrganisms().size() == 2);
        REQUIRE(world.getOrganisms()[0]->getSubspecies() == "W");
        REQUIRE(world.getOrganisms()[1]->getSubspecies() == "G");
    }
}

TEST_CASE("After an organism dies it is still present in ancestor history", "[World]") {
    World world{};
    OrganismFactory factory{};

    auto org1 = factory.createWolf(Position(1, 2));
    org1->setLineageInfo(LineageInfo(1));

    auto org2 = factory.createWolf(Position(3, 4));
    org2->setLineageInfo(LineageInfo(2, org1));

    world.addOrganism(org1);
    world.addOrganism(org2);

    world.markOrganismAsDead(org1, 3);
    world.removeDeadOrganisms();

    REQUIRE(world.getOrganisms().size() == 1);
    REQUIRE(org2->getAncestorHistory().size() == 1);
    REQUIRE(org2->getAncestorHistory()[0]->getSubspecies() == "W");
}

TEST_CASE("Organisms kill other animals according to their attack capabilities", "[World]") {
    World world{};
    OrganismFactory factory{};

    auto wolf = factory.createWolf();
    auto sheep = factory.createSheep();
    auto grass = factory.createGrass();
    auto toadstool = factory.createToadstool();

    SECTION("Wolf attacks and kills Sheep") {
        world.addOrganism(wolf);
        world.addOrganism(sheep);
        auto result = wolf->attack(world.getOrganismsFromPosition(sheep->getPosition()));

        REQUIRE(result.has_value());
        REQUIRE(result.value()->getSubspecies() == "S");
    }

    SECTION("Sheep cannot attack Wolf") {
        world.addOrganism(sheep);
        world.addOrganism(wolf);
        auto result = sheep->attack(world.getOrganismsFromPosition(wolf->getPosition()));

        REQUIRE_FALSE(result.has_value());
    }

    SECTION("Grass cannot attack any organism") {
        world.addOrganism(grass);
        world.addOrganism(wolf);
        world.addOrganism(sheep);
        auto resultWolf = grass->attack(world.getOrganismsFromPosition(wolf->getPosition()));
        auto resultSheep = grass->attack(world.getOrganismsFromPosition(sheep->getPosition()));

        REQUIRE_FALSE(resultWolf.has_value());
        REQUIRE_FALSE(resultSheep.has_value());
    }

    SECTION("Toadstool cannot attack a wolf") {
        world.addOrganism(toadstool);
        world.addOrganism(wolf);
        auto resultWolf = toadstool->attack(world.getOrganismsFromPosition(wolf->getPosition()));

        REQUIRE_FALSE(resultWolf.has_value());
    }

    SECTION("Toadstool can attack a sheep") {
        world.addOrganism(toadstool);
        world.addOrganism(sheep);
        auto resultSheep = toadstool->attack(world.getOrganismsFromPosition(sheep->getPosition()));

        REQUIRE(resultSheep.has_value());
        REQUIRE(resultSheep.value()->getSubspecies() == "S");
    }

    SECTION("Sheep can attack Grass") {
        world.addOrganism(sheep);
        world.addOrganism(grass);
        auto resultGrass = sheep->attack(world.getOrganismsFromPosition(grass->getPosition()));

        REQUIRE(resultGrass.has_value());
        REQUIRE(resultGrass.value()->getSubspecies() == "G");
    }
}

TEST_CASE("World constructors", "[World]") {
    SECTION("Default constructor creates world with default dimensions") {
        World world{};
        REQUIRE(world.getWorldX() == 6);
        REQUIRE(world.getWorldY() == 6);
        REQUIRE(world.getStartWorldX() == 0);
        REQUIRE(world.getStartWorldY() == 0);
    }

    SECTION("Parameterized constructor with dimensions") {
        World world(10, 15);
        REQUIRE(world.getWorldX() == 10);
        REQUIRE(world.getWorldY() == 15);
    }

    SECTION("Parameterized constructor with all parameters") {
        World world(10, 15, 2, 3);
        REQUIRE(world.getWorldX() == 10);
        REQUIRE(world.getWorldY() == 15);
        REQUIRE(world.getStartWorldX() == 2);
        REQUIRE(world.getStartWorldY() == 3);
    }

    SECTION("Constructor with zero dimensions throws exception") {
        REQUIRE_THROWS_AS([]() { World world(0, 0); }(), std::invalid_argument);
    }
}

TEST_CASE("World equality operator", "[World]") {
    SECTION("Two worlds with same dimensions are equal") {
        World world1(10, 15, 2, 3);
        World world2(10, 15, 2, 3);
        REQUIRE(world1 == world2);
    }

    SECTION("Two empty default worlds are equal") {
        World world1{};
        World world2{};
        REQUIRE(world1 == world2);
    }

    SECTION("Two worlds with different X dimensions are not equal") {
        World world1(10, 15);
        World world2(12, 15);
        REQUIRE(!(world1 == world2));
    }

    SECTION("Two worlds with different Y dimensions are not equal") {
        World world1(10, 15);
        World world2(10, 20);
        REQUIRE(!(world1 == world2));
    }
}

TEST_CASE("World organism retrieval from position", "[World]") {
    World world{};
    OrganismFactory factory{};

    SECTION("getOrganismsFromPosition returns empty vector when no organisms at position") {
        Position pos(2, 3);
        auto organisms = world.getOrganismsFromPosition(pos);
        REQUIRE(organisms.empty());
    }

    SECTION("getOrganismsFromPosition returns organism when at position") {
        auto wolf = factory.createWolf(Position(3, 4));
        world.addOrganism(wolf);
        
        auto organisms = world.getOrganismsFromPosition(Position(3, 4));
        REQUIRE(organisms.size() == 1);
        REQUIRE(organisms[0]->getSubspecies() == "W");
    }

    SECTION("getOrganismsFromPosition returns multiple organisms at same position") {
        auto wolf = factory.createWolf(Position(3, 4));
        auto sheep = factory.createSheep(Position(3, 4));
        auto grass = factory.createGrass(Position(3, 4));
        
        world.addOrganism(wolf);
        world.addOrganism(sheep);
        world.addOrganism(grass);
        
        auto organisms = world.getOrganismsFromPosition(Position(3, 4));
        REQUIRE(organisms.size() == 3);
    }
}

TEST_CASE("World organism power and live length modifications", "[World]") {
    World world{};
    OrganismFactory factory{};

    SECTION("increaseOrganismsPowerBy increases power of all organisms") {
        auto wolf = factory.createWolf();
        auto sheep = factory.createSheep();
        auto grass = factory.createGrass();
        
        int initialWolfPower = wolf->getPower();
        int initialSheepPower = sheep->getPower();
        int initialGrassPower = grass->getPower();
        
        world.addOrganism(wolf);
        world.addOrganism(sheep);
        world.addOrganism(grass);
        
        world.increaseOrganismsPowerBy(3);
        
        REQUIRE(wolf->getPower() == initialWolfPower + 3);
        REQUIRE(sheep->getPower() == initialSheepPower + 3);
        REQUIRE(grass->getPower() == initialGrassPower + 3);
    }

    SECTION("decreaseOrganismsLiveLengthBy decreases live length of all organisms") {
        auto wolf = factory.createWolf();
        auto sheep = factory.createSheep();
        auto grass = factory.createGrass();
        
        wolf->setLiveLength(10);
        sheep->setLiveLength(15);
        grass->setLiveLength(20);
        
        world.addOrganism(wolf);
        world.addOrganism(sheep);
        world.addOrganism(grass);
        
        world.decreaseOrganismsLiveLengthBy(2);
        
        REQUIRE(wolf->getLiveLength() == 8);
        REQUIRE(sheep->getLiveLength() == 13);
        REQUIRE(grass->getLiveLength() == 18);
    }

    SECTION("increaseOrganismsPowerBy doesn't affect empty world") {
        World emptyWorld{};
        emptyWorld.increaseOrganismsPowerBy(5);
        REQUIRE(emptyWorld.getOrganisms().empty());
    }
}

TEST_CASE("World organism play turn eligibility", "[World]") {
    World world{};
    OrganismFactory factory{};

    SECTION("Organism can play turn when alive") {
        auto wolf = factory.createWolf();
        REQUIRE(world.organismCanPlayTurn(wolf) == true);
    }

    SECTION("Organism cannot play turn when dead") {
        auto wolf = factory.createWolf();
        wolf->setDeathTurn(5);
        REQUIRE(world.organismCanPlayTurn(wolf) == false);
    }

    SECTION("Organism cannot play turn when live length is 0") {
        auto wolf = factory.createWolf();
        wolf->setLiveLength(0);
        REQUIRE(world.organismCanPlayTurn(wolf) == false);
    }
}

TEST_CASE("World positions around organism", "[World]") {
    World world(10, 10);
    OrganismFactory factory{};

    SECTION("getPositionsAround returns correct number of adjacent positions") {
        auto organism = factory.createWolf(Position(5, 5));
        world.addOrganism(organism);
        
        auto positions = world.getPositionsAround(organism);
        REQUIRE(positions.size() == 8);
    }

    SECTION("getPositionsAround for organism at corner has fewer positions") {
        auto organism = factory.createWolf(Position(0, 0));
        world.addOrganism(organism);
        
        auto positions = world.getPositionsAround(organism);
        REQUIRE(positions.size() == 3);
    }

    SECTION("getValidPositionsAround returns only free positions for animal and plant") {
        auto wolf = factory.createWolf(Position(5, 5));
        auto grass = factory.createGrass(Position(5, 6));
        
        world.addOrganism(wolf);
        world.addOrganism(grass);
        
        auto validPositions = world.getValidPositionsAround(wolf);
        REQUIRE(validPositions.size() == 8);
    }

    SECTION("getValidPositionsAround returns only free positions for animal and animal") {
        auto wolf = factory.createWolf(Position(5, 5));
        auto sheep = factory.createSheep(Position(5, 6));
        
        world.addOrganism(wolf);
        world.addOrganism(sheep);
        
        auto validPositions = world.getValidPositionsAround(wolf);
        REQUIRE(validPositions.size() == 7);
    }
}

TEST_CASE("World with multiple organisms maintains integrity", "[World]") {
    World world{};
    OrganismFactory factory{};

    SECTION("Adding and removing organisms maintains world state") {
        auto wolf1 = factory.createWolf();
        auto wolf2 = factory.createWolf();
        auto sheep = factory.createSheep();
        
        world.addOrganism(wolf1);
        world.addOrganism(wolf2);
        world.addOrganism(sheep);
        
        world.markOrganismAsDead(wolf1, 5);
        world.removeDeadOrganisms();
        REQUIRE(world.getOrganisms().size() == 2);
    }

    SECTION("Removing all organisms leaves empty world") {
        auto wolf = factory.createWolf();
        auto sheep = factory.createSheep();
        
        world.addOrganism(wolf);
        world.addOrganism(sheep);
        world.markOrganismAsDead(wolf, 1);
        world.markOrganismAsDead(sheep, 2);
        world.removeDeadOrganisms();
        
        REQUIRE(world.getOrganisms().empty());
    }
}