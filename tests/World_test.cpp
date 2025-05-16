#include "World.hpp"
#include "organisms/Grass.hpp"
#include "organisms/Sheep.hpp"
#include "organisms/Wolf.hpp"
#include "organisms/Toadstool.hpp"
#include <catch2/catch_test_macros.hpp>

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

    Wolf org1{};
    Sheep org2{};
    Grass org3{};
    Toadstool org4{};

    world.addOrganism(org2);
    world.addOrganism(org1);
    world.addOrganism(org4);
    world.addOrganism(org3);
    world.addOrganism(org1);

    REQUIRE(world.getOrganisms()[0].getSpecies() == "W");
    REQUIRE(world.getOrganisms()[1].getSpecies() == "W");
    REQUIRE(world.getOrganisms()[2].getSpecies() == "S");
    REQUIRE(world.getOrganisms()[3].getSpecies() == "T");
    REQUIRE(world.getOrganisms()[4].getSpecies() == "G");
}