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