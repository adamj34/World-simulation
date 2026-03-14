#include "organisms/Organism.hpp"
#include "organisms/OrganismFactory.hpp"
#include "organisms/SpeciesCodes.hpp"
#include "organisms/Wolf.hpp"
#include <catch2/catch_test_macros.hpp>

const SpeciesCodes WOLF_SPECIES = SpeciesCodes::Wolf;
const SpeciesCodes SPECIES = SpeciesCodes::Animal;

TEST_CASE("Organism class core functionality", "[Organism]") {
    OrganismFactory factory{};

    SECTION("Default constructor initializes member variables correctly") {
        auto org{ factory.createWolf() };
        REQUIRE(org->getPower() == 8);
        REQUIRE(org->getPosition().getX() == 0);
        REQUIRE(org->getPosition().getY() == 0);
        REQUIRE(org->getSpecies() == SPECIES);
        REQUIRE(org->getSubspecies() == WOLF_SPECIES);
    }

    SECTION("Parameterized constructor initializes member variables correctly") {
        auto org{ factory.createWolf(Position{ 3, 4 }) };
        REQUIRE(org->getPower() == 8);
        REQUIRE(org->getPosition().getX() == 3);
        REQUIRE(org->getPosition().getY() == 4);
        REQUIRE(org->getSpecies() == SPECIES);
        REQUIRE(org->getSubspecies() == WOLF_SPECIES);
    }

    SECTION("Move method updates position correctly") {
        auto org{ factory.createSheep(Position{ 1, 2 }) };
        Position newPos{ 3, 4 };
        org->move(newPos);
        REQUIRE(org->getPosition().getX() == 3);
        REQUIRE(org->getPosition().getY() == 4);
    }

    SECTION("Power cannot be negative") {
        Position pos{ 3, 4 };
        REQUIRE_THROWS_AS(Wolf(-5, pos), std::invalid_argument);
    }

    SECTION("Power to reproduce cannot be negative") {
        Position pos{ 3, 4 };
        Wolf org(5, pos);
        REQUIRE_THROWS_AS(org.setPowerToReproduce(-4), std::invalid_argument);
    }

    SECTION("Live length cannot be negative") {
        Position pos{ 3, 4 };
        Wolf org(5, pos);
        REQUIRE_THROWS_AS(org.setLiveLength(-9), std::invalid_argument);
    }
}

TEST_CASE("Organism class copy constructor and assignment operator", "[Organism]") {
    SECTION("Copy constructor creates a new object with the same values") {
        Position pos{ 3, 4 };
        Wolf org1(5, pos);
        Wolf org2 = { org1 };          // Copy constructor
        REQUIRE(org2.getPower() == 8); // Default power for Wolf
        REQUIRE(org2.getPosition().getX() == 3);
        REQUIRE(org2.getPosition().getY() == 4);
    }

    SECTION("Copy assignment operator assigns values correctly") {
        Position pos1{ 3, 4 };
        Wolf org1(5, pos1);
        Position pos2{ 6, 7 };
        Wolf org2(10, pos2);
        org2 = org1; // Copy assignment operator
        REQUIRE(org2.getPower() == 5);
        REQUIRE(org2.getPosition().getX() == 3);
        REQUIRE(org2.getPosition().getY() == 4);
    }

    SECTION("Copy constructor does not affect original object in the case of primitive obects") {
        Position pos{ 3, 4 };
        Wolf org1(5, pos);
        Wolf org2 = { org1 }; // Copy constructor
        org2.setPower(10);
        REQUIRE(org1.getPower() == 5); // Original object should not be affected
    }

    SECTION("Copy assignment operator does not affect original object in the case of complex objects") {
        Position pos1{ 3, 4 };
        Wolf org1(5, pos1);
        Position pos2{ 6, 7 };
        Wolf org2(10, pos2);
        org2 = org1; // Copy assignment operator
        org1.setPosition(Position(15, 15));
        REQUIRE(org2.getPosition().getX() == 3); // Original object should not be affected
        REQUIRE(org2.getPosition().getY() == 4); // Original object should not be affected
    }
}

TEST_CASE("Organism reproduction and alive logic", "[Organism]") {
    OrganismFactory factory{};

    SECTION("canReproduce returns true when power equals powerToReproduce") {
        Position pos{ 3, 4 };
        Wolf org(5, pos);
        org.setPowerToReproduce(5);
        REQUIRE(org.canReproduce() == true);
    }

    SECTION("canReproduce returns true when power exceeds powerToReproduce") {
        Position pos{ 3, 4 };
        Wolf org(10, pos);
        org.setPowerToReproduce(5);
        REQUIRE(org.canReproduce() == true);
    }

    SECTION("canReproduce returns false when power is below powerToReproduce") {
        Position pos{ 3, 4 };
        Wolf org(3, pos);
        org.setPowerToReproduce(5);
        REQUIRE(org.canReproduce() == false);
    }

    SECTION("isAlive returns true for newly created organism") {
        auto org{ factory.createWolf() };
        REQUIRE(org->isAlive() == true);
    }

    SECTION("isAlive returns false after organism is marked dead") {
        auto org{ factory.createWolf() };
        org->setDeathTurn(10);
        REQUIRE(org->isAlive() == false);
    }

    SECTION("setDeathTurn cannot be negative") {
        Position pos{ 3, 4 };
        Wolf org(5, pos);
        REQUIRE_THROWS_AS(org.setDeathTurn(-1), std::invalid_argument);
    }

    SECTION("setDeathTurn stores the death turn correctly") {
        Position pos{ 3, 4 };
        Wolf org(5, pos);
        org.setDeathTurn(25);
        REQUIRE(org.getLineageInfo().deathTurn == 25);
    }
}

TEST_CASE("Organism equality operator", "[Organism]") {
    SECTION("Two organisms with same properties are equal") {
        Position pos{ 3, 4 };
        Wolf org1(5, pos);
        Wolf org2(5, pos);
        org1.setSpecies(SpeciesCodes::Animal);
        org2.setSpecies(SpeciesCodes::Animal);
        REQUIRE(org1 == org2);
    }

    SECTION("Two organisms with different power are not equal") {
        Position pos{ 3, 4 };
        Wolf org1(5, pos);
        Wolf org2(10, pos);
        org1.setSpecies(SpeciesCodes::Animal);
        org2.setSpecies(SpeciesCodes::Animal);
        REQUIRE(!(org1 == org2));
    }

    SECTION("Two organisms with different initiative are not equal") {
        Position pos{ 3, 4 };
        Wolf org1(5, pos);
        Wolf org2(5, pos);
        org1.setInitiative(1);
        org2.setInitiative(2);
        org1.setSpecies(SpeciesCodes::Animal);
        org2.setSpecies(SpeciesCodes::Animal);
        REQUIRE(!(org1 == org2));
    }

    SECTION("Two organisms with different position are not equal") {
        Wolf org1(5, Position{ 3, 4 });
        Wolf org2(5, Position{ 5, 6 });
        org1.setSpecies(SpeciesCodes::Animal);
        org2.setSpecies(SpeciesCodes::Animal);
        REQUIRE(!(org1 == org2));
    }

    SECTION("Two organisms with different species are not equal") {
        Position pos{ 3, 4 };
        Wolf org1(5, pos);
        Wolf org2(5, pos);
        org1.setSpecies(SpeciesCodes::Animal);
        org2.setSpecies(SpeciesCodes::Plant);
        REQUIRE(!(org1 == org2));
    }
}

TEST_CASE("Organism full constructor", "[Organism]") {
    SECTION("Full parameterized constructor initializes all members correctly") {
        Position pos{ 5, 6 };
        Wolf org(10, 3, 20, 5, pos);
        REQUIRE(org.getPower() == 10);
        REQUIRE(org.getInitiative() == 3);
        REQUIRE(org.getLiveLength() == 20);
        REQUIRE(org.getPowerToReproduce() == 5);
        REQUIRE(org.getPosition().getX() == 5);
        REQUIRE(org.getPosition().getY() == 6);
    }

    SECTION("Full parameterized constructor validates power is not negative") {
        Position pos{ 5, 6 };
        REQUIRE_THROWS_AS(Wolf(-1, 3, 20, 5, pos), std::invalid_argument);
    }

    SECTION("Full parameterized constructor validates initiative is not negative") {
        Position pos{ 5, 6 };
        REQUIRE_THROWS_AS(Wolf(10, -1, 20, 5, pos), std::invalid_argument);
    }

    SECTION("Full parameterized constructor validates liveLength is not negative") {
        Position pos{ 5, 6 };
        REQUIRE_THROWS_AS(Wolf(10, 3, -1, 5, pos), std::invalid_argument);
    }

    SECTION("Full parameterized constructor validates powerToReproduce is not negative") {
        Position pos{ 5, 6 };
        REQUIRE_THROWS_AS(Wolf(10, 3, 20, -1, pos), std::invalid_argument);
    }
}
