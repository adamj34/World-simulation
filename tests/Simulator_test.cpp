#include "Simulator.hpp"
#include "World.hpp"
#include "organisms/OrganismFactory.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Simulator mutates provided world during turn", "[Simulator]") {
    World world{ 8, 8 };
    OrganismFactory factory{};

    auto sheep = factory.createSheep(Position{ 4, 4 });
    world.addOrganism(sheep);

    const Position initialPosition = sheep->getPosition();

    Simulator simulator{ world };
    simulator.playTurn();

    const Position updatedPosition = sheep->getPosition();
    REQUIRE_FALSE(updatedPosition == initialPosition);
}

TEST_CASE("Simulator uses deterministic RNG when seeded", "[Simulator]") {
    World worldA{ 8, 8 };
    World worldB{ 8, 8 };
    OrganismFactory factory{};

    auto sheepA = factory.createSheep(Position{ 4, 4 });
    auto sheepB = factory.createSheep(Position{ 4, 4 });
    worldA.addOrganism(sheepA);
    worldB.addOrganism(sheepB);

    const Position initialA = sheepA->getPosition();
    const Position initialB = sheepB->getPosition();

    Simulator simulatorA{ worldA, 42U };
    Simulator simulatorB{ worldB, 42U };

    simulatorA.playTurn();
    simulatorB.playTurn();

    REQUIRE_FALSE(sheepA->getPosition() == initialA);
    REQUIRE_FALSE(sheepB->getPosition() == initialB);
    REQUIRE(worldA == worldB);
}
