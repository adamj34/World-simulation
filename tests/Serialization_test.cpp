#include "Simulator.hpp"
#include "World.hpp"
#include "serialization.hpp"
#include "organisms/OrganismFactory.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string> 

TEST_CASE("World serialization and deserialization", "[Serialization]") {
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

TEST_CASE("Empty world serialization", "[Serialization]") {
    SECTION("Empty world can be serialized and deserialized") {
        World world{ 5, 5 };
        const std::string filename = "emptyWorldTest.bin";
        
        boost::serialization::saveWorld(world, filename);
        
        World loadedWorld{ 1, 1 };
        boost::serialization::loadWorld(loadedWorld, filename);
        
        REQUIRE(world == loadedWorld);
        REQUIRE(loadedWorld.getOrganisms().empty());
    }
}

TEST_CASE("Single organism serialization", "[Serialization]") {
    OrganismFactory factory{};
    
    SECTION("Wolf serialization preserves all properties") {
        World world{ 10, 10 };
        auto wolf = factory.createWolf(Position{ 3, 4 });
        wolf->setPower(15);
        wolf->setInitiative(5);
        wolf->setLiveLength(12);
        wolf->setPowerToReproduce(8);
        
        world.addOrganism(wolf);
        
        const std::string filename = "wolfTest.bin";
        boost::serialization::saveWorld(world, filename);
        
        World loadedWorld{};
        boost::serialization::loadWorld(loadedWorld, filename);
        
        REQUIRE(loadedWorld.getOrganisms().size() == 1);
        REQUIRE(loadedWorld.getOrganisms()[0]->getSubspecies() == "W");
        REQUIRE(loadedWorld.getOrganisms()[0]->getPosition().getX() == 3);
        REQUIRE(loadedWorld.getOrganisms()[0]->getPosition().getY() == 4);
        REQUIRE(loadedWorld.getOrganisms()[0]->getPower() == 15);
        REQUIRE(loadedWorld.getOrganisms()[0]->getInitiative() == 5);
        REQUIRE(loadedWorld.getOrganisms()[0]->getLiveLength() == 12);
        REQUIRE(loadedWorld.getOrganisms()[0]->getPowerToReproduce() == 8);
    }
    
    SECTION("Sheep serialization preserves all properties") {
        World world{ 10, 10 };
        auto sheep = factory.createSheep(Position{ 5, 6 });
        sheep->setPower(10);
        sheep->setLiveLength(20);
        
        world.addOrganism(sheep);
        
        const std::string filename = "sheepTest.bin";
        boost::serialization::saveWorld(world, filename);
        
        World loadedWorld{};
        boost::serialization::loadWorld(loadedWorld, filename);
        
        REQUIRE(loadedWorld.getOrganisms()[0]->getSubspecies() == "S");
        REQUIRE(loadedWorld.getOrganisms()[0]->getPosition().getX() == 5);
        REQUIRE(loadedWorld.getOrganisms()[0]->getPosition().getY() == 6);
    }

    SECTION("Toadstool serialization preserves all properties") {
        World world{ 10, 10 };
        auto toadstool = factory.createToadstool(Position{ 2, 3 });
        
        world.addOrganism(toadstool);
        
        const std::string filename = "toadsToolTest.bin";
        boost::serialization::saveWorld(world, filename);
        
        World loadedWorld{};
        boost::serialization::loadWorld(loadedWorld, filename);
        
        REQUIRE(loadedWorld.getOrganisms()[0]->getSubspecies() == "T");
    }
}

TEST_CASE("Multiple organisms serialization", "[Serialization]") {
    SECTION("Multiple organisms preserve order and properties") {
        World world{ 10, 10 };
        OrganismFactory factory{};
        
        auto wolf1 = factory.createWolf(Position{ 1, 1 });
        auto wolf2 = factory.createWolf(Position{ 2, 2 });
        auto sheep = factory.createSheep(Position{ 3, 3 });
        auto grass = factory.createGrass(Position{ 4, 4 });
        
        wolf1->setPower(20);
        sheep->setPower(12);
        
        world.addOrganism(wolf1);
        world.addOrganism(wolf2);
        world.addOrganism(sheep);
        world.addOrganism(grass);
        
        const std::string filename = "multiOrganismTest.bin";
        boost::serialization::saveWorld(world, filename);
        
        World loadedWorld{};
        boost::serialization::loadWorld(loadedWorld, filename);
        
        REQUIRE(loadedWorld.getOrganisms().size() == 4);
        REQUIRE(loadedWorld.getOrganisms()[0]->getPower() == 20);
        REQUIRE(loadedWorld.getOrganisms()[2]->getPower() == 12);
    }
}

TEST_CASE("Organism with lineage info serialization", "[Serialization]") {
    SECTION("Organism lineage info is preserved through serialization") {
        World world{ 10, 10 };
        OrganismFactory factory{};
        
        auto parent = factory.createWolf(Position{ 1, 1 });
        parent->setLineageInfo(LineageInfo(5));
        
        auto child = factory.createWolf(Position{ 2, 2 });
        child->setLineageInfo(LineageInfo(10, parent));
        
        world.addOrganism(parent);
        world.addOrganism(child);
        
        const std::string filename = "lineageTest.bin";
        boost::serialization::saveWorld(world, filename);
        
        World loadedWorld{};
        boost::serialization::loadWorld(loadedWorld, filename);
        
        REQUIRE(loadedWorld.getOrganisms().size() == 2);
        auto loadedChild = loadedWorld.getOrganisms()[1];
        auto ancestors = loadedChild->getAncestorHistory();
        REQUIRE(ancestors.size() == 1);
    }
}

TEST_CASE("Dead organism serialization", "[Serialization]") {
    SECTION("Dead organisms are preserved in serialization") {
        World world{ 10, 10 };
        OrganismFactory factory{};
        
        auto wolf = factory.createWolf(Position{ 3, 4 });
        world.addOrganism(wolf);
        world.markOrganismAsDead(wolf, 15);
        
        const std::string filename = "deadOrganismTest.bin";
        boost::serialization::saveWorld(world, filename);
        
        World loadedWorld{};
        boost::serialization::loadWorld(loadedWorld, filename);
        
        REQUIRE(loadedWorld.getOrganisms().size() == 1);
        REQUIRE(loadedWorld.getOrganisms()[0]->getLineageInfo().deathTurn == 15);
        REQUIRE(loadedWorld.getOrganisms()[0]->isAlive() == false);
    }
}

TEST_CASE("Loading overwrites previous world state", "[Serialization]") {
    SECTION("Loading a saved world overwrites the current world") {
        World world1{ 10, 10 };
        OrganismFactory factory{};
        
        auto wolf = factory.createWolf(Position{ 2, 2 });
        world1.addOrganism(wolf);
        
        const std::string filename = "overwriteTest.bin";
        boost::serialization::saveWorld(world1, filename);
        
        World world2{ 5, 5 };
        auto sheep = factory.createSheep(Position{ 1, 1 });
        world2.addOrganism(sheep);
        
        REQUIRE(world2.getOrganisms().size() == 1);
        REQUIRE(world2.getWorldX() == 5);
        
        boost::serialization::loadWorld(world2, filename);
        
        REQUIRE(world2.getWorldX() == 10);
        REQUIRE(world2.getWorldY() == 10);
        REQUIRE(world2.getOrganisms().size() == 1);
        REQUIRE(world2.getOrganisms()[0]->getSubspecies() == "W");
    }
}

TEST_CASE("Multiple save and load cycles", "[Serialization]") {
    SECTION("Multiple serialization and deserialization cycles preserve data") {
        World world{ 8, 8 };
        OrganismFactory factory{};
        
        auto wolf = factory.createWolf(Position{ 2, 2 });
        wolf->setPower(18);
        world.addOrganism(wolf);
        
        const std::string filename = "multiCycleTest.bin";
        
        // First cycle
        boost::serialization::saveWorld(world, filename);
        World loaded1{};
        boost::serialization::loadWorld(loaded1, filename);
        
        // Second cycle
        boost::serialization::saveWorld(loaded1, filename);
        World loaded2{};
        boost::serialization::loadWorld(loaded2, filename);
        
        REQUIRE(loaded2.getWorldX() == 8);
        REQUIRE(loaded2.getWorldY() == 8);
        REQUIRE(loaded2.getOrganisms()[0]->getPower() == 18);
        REQUIRE(loaded2.getOrganisms()[0]->getPosition().getX() == 2);
    }
}