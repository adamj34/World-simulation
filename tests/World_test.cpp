#include "Position.hpp"
#include "World.hpp"
#include "organisms/Grass.hpp"
#include "organisms/Sheep.hpp"
#include "organisms/Toadstool.hpp"
#include "organisms/Wolf.hpp"
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

    auto org1 = std::make_shared<Wolf>();
    auto org2 = std::make_shared<Sheep>();
    auto org3 = std::make_shared<Grass>();
    auto org4 = std::make_shared<Toadstool>();
    auto org5 = std::make_shared<Wolf>();

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

    auto org1 = std::make_shared<Wolf>();
    auto org2 = std::make_shared<Sheep>();
    auto org3 = std::make_shared<Grass>();

    world.addOrganism(org1);
    world.addOrganism(org2);
    world.addOrganism(org3);

    std::shared_ptr<Organism> organism_to_kill = org1;
    world.markOrganismAsDead(organism_to_kill, 1);
    org2->setLiveLength(0);
    
    world.removeDeadOrganisms();

    REQUIRE(world.getOrganisms().size() == 1);
    REQUIRE(world.getOrganisms()[0]->getSubspecies() == "G");
}

