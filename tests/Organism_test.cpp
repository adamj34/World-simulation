#include "organisms/Organism.hpp"
#include "organisms/OrganismFactory.hpp"
#include "organisms/Wolf.hpp"
#include <catch2/catch_test_macros.hpp>

const std::string WOLF_SPECIES = "W";
const std::string SPECIES = "A";

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

TEST_CASE("Organism class lineage info", "[Organism]") {
    OrganismFactory factory{};

    SECTION("Ancestor history is retrieved correctly") {
        auto org1 = factory.createWolf();
        org1->setLineageInfo(LineageInfo(1));

        auto org2 = factory.createWolf();
        org2->setLineageInfo(LineageInfo(2, org1));

        auto org3 = factory.createWolf();
        org3->setLineageInfo(LineageInfo(3, org2));

        auto org4 = factory.createWolf();
        org4->setLineageInfo(LineageInfo(4, org3));

        std::vector<std::shared_ptr<Organism>> ancestors = org4->getAncestorHistory();
        REQUIRE(ancestors.size() == 3);
        REQUIRE(ancestors[2] == org1);
        REQUIRE(ancestors[1] == org2);
        REQUIRE(ancestors[0] == org3);
        REQUIRE(org3->getLineageInfo().parent == org2);
        REQUIRE(org2->getLineageInfo().parent == org1);
        REQUIRE(org4->getLineageInfo().parent == org3);
    }

    SECTION("Ancestor history is empty for an organism with no parent") {
        auto org = factory.createWolf();
        org->setLineageInfo(LineageInfo(1));

        std::vector<std::shared_ptr<Organism>> ancestors = org->getAncestorHistory();
        REQUIRE(ancestors.empty());
    }
}
