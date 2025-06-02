#include "Simulator.hpp"
#include "World.hpp"
#include "serialization.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string> // Required for std::string

TEST_CASE("World serialization and deserialization", "[World]") {
    World world{ 10, 10, 0, 0 };

    auto wolf = std::make_shared<Wolf>(5, Position{ 1, 1 });
    auto sheep = std::make_shared<Sheep>(3, Position{ 2, 2 });
    auto grass = std::make_shared<Grass>(1, Position{ 3, 3 });
    auto toadstool = std::make_shared<Toadstool>(2, Position{ 4, 4 });

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

        simulator.playTurn();
        simulator.playTurn();

        boost::serialization::loadWorld(world, filename_section2);

        REQUIRE(expectedWorldAtState1 == world);
    }
}