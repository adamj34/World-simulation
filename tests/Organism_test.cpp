#include <catch2/catch_test_macros.hpp>
#include "organisms/Organism.hpp"

TEST_CASE("Organism class core functionality", "[Organism]") {
    SECTION("Default constructor initializes member variables correctly") {
        Organism org {};
        REQUIRE(org.getPower() == 0);
        REQUIRE(org.getPosition().getX() == 0);
        REQUIRE(org.getPosition().getY() == 0);
        REQUIRE(org.getSpecies() == "O");
    }

    SECTION("Parameterized constructor initializes member variables correctly") {
        Position pos{3, 4};
        Organism org(5, pos);
        REQUIRE(org.getPower() == 5);
        REQUIRE(org.getPosition().getX() == 3);
        REQUIRE(org.getPosition().getY() == 4);
        REQUIRE(org.getSpecies() == "O");
    }

    SECTION("Move method updates position correctly") {
        Position pos{1, 2};
        Organism org(5, pos);
        org.move(3, 4);
        REQUIRE(org.getPosition().getX() == 4);
        REQUIRE(org.getPosition().getY() == 6);
    }

    SECTION("Power cannot be negative") {
        Position pos{3, 4};
        REQUIRE_THROWS_AS(Organism(-5, pos), std::invalid_argument);
    }

    SECTION("Power to reproduce cannot be negative") {
        Position pos{3, 4};
        Organism org(5, pos);
        REQUIRE_THROWS_AS(org.setPowerToReproduce(-4), std::invalid_argument);
    }

    SECTION("Live length cannot be negative") {
        Position pos{3, 4};
        Organism org(5, pos);
        REQUIRE_THROWS_AS(org.setLiveLength(-9), std::invalid_argument);
    }

}

TEST_CASE("Organism class copy constructor and assignment operator", "[Organism]") {
    SECTION("Copy constructor creates a new object with the same values") {
        Position pos{3, 4};
        Organism org1(5, pos);
        Organism org2 = { org1 }; // Copy constructor
        REQUIRE(org2.getPower() == 5);
        REQUIRE(org2.getPosition().getX() == 3);
        REQUIRE(org2.getPosition().getY() == 4);
    }

    SECTION("Copy assignment operator assigns values correctly") {
        Position pos1{3, 4};
        Organism org1(5, pos1);
        Position pos2{6, 7};
        Organism org2(10, pos2);
        org2 = org1; // Copy assignment operator
        REQUIRE(org2.getPower() == 5);
        REQUIRE(org2.getPosition().getX() == 3);
        REQUIRE(org2.getPosition().getY() == 4);
    }

    SECTION("Copy constructor does not affect original object in the case of primitive obects") {
        Position pos{3, 4};
        Organism org1(5, pos);
        Organism org2 = { org1 }; // Copy constructor
        org2.setPower(10);
        REQUIRE(org1.getPower() == 5); // Original object should not be affected
    }

    SECTION("Copy assignment operator does not affect original object in the case of complex objects") {
        Position pos1{3, 4};
        Organism org1(5, pos1);
        Position pos2{6, 7};
        Organism org2(10, pos2);
        org2 = org1; // Copy assignment operator
        org1.test_change_x(10);
        REQUIRE(org2.getPosition().getX() == 3); // Original object should not be affected

    }

    SECTION("Copy assignment operator does not affect original object in the case of primitive objects") {
        Position pos1{3, 4};
        Organism org1(5, pos1);
        Position pos2{6, 7};
        Organism org2(10, pos2);
        org2 = org1; // Copy assignment operator
        org2.test_change_x(10);
        REQUIRE(org2.getPosition().getX() == 10); // Copied object should be affected
        REQUIRE(org1.getPosition().getX() == 3); // Original object should not be affected
    }
}