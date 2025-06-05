#include "Simulator.hpp"
#include "World.hpp"
#include "serialization.hpp"
#include "organisms/OrganismFactory.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string> 

TEST_CASE("World serialization and deserialization", "[World]") {
    World world{ 10, 10, 0, 0 };
    OrganismFactory factory{};

    auto wolf = factory.createWolf(Position{ 1, 1 });
    auto sheep = factory.createSheep(Position{ 2, 2 });
    auto grass = factory.createGrass(Position{ 3, 3 });
    auto toadstool = factory.createToadstool(Position{ 4, 4 });

    world.addOrganism(wolf);
    world.addOrganism(sheep);
    world.addOrganism(grass);
    world.addOrganism(toadstool);

    SECTION("World serialization and deserialization does not change the world") {

        const std::string filename_section1 = "worldTest_section1.bin";
        boost::serialization::saveWorld(world, filename_section1);

        World loadedWorld{};
        boost::serialization::loadWorld(loadedWorld, filename_section1);

        REQUIRE(world == loadedWorld);
    }

    SECTION("World serialization and deserialization after making turns") {

        Simulator simulator{ world };
        simulator.playTurn();

        const std::string filename_section2 = "worldTest_section2.bin";
        boost::serialization::saveWorld(world, filename_section2);

        World expectedWorldAtState1{};
        boost::serialization::loadWorld(expectedWorldAtState1, filename_section2);

        simulator.runSimulation();

        boost::serialization::loadWorld(world, filename_section2);

        REQUIRE(expectedWorldAtState1 == world);
    }
}