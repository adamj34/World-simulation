#include "organisms/Organism.hpp"
#include "organisms/OrganismFactory.hpp"
#include "organisms/Wolf.hpp"
#include "organisms/Lineage.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("LineageService getAncestorHistory", "[LineageService]") {
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

        std::vector<std::shared_ptr<Organism>> ancestors = LineageService::getAncestorHistory(*org4);
        REQUIRE(ancestors.size() == 3);
        REQUIRE(ancestors[2] == org1);
        REQUIRE(ancestors[1] == org2);
        REQUIRE(ancestors[0] == org3);
        REQUIRE(org3->getParent() == org2);
        REQUIRE(org2->getParent() == org1);
        REQUIRE(org4->getParent() == org3);
    }

    SECTION("Ancestor history is empty for an organism with no parent") {
        auto org = factory.createWolf();
        org->setLineageInfo(LineageInfo(1));

        std::vector<std::shared_ptr<Organism>> ancestors = LineageService::getAncestorHistory(*org);
        REQUIRE(ancestors.empty());
    }
}

TEST_CASE("LineageService printAncestorHistory", "[LineageService]") {
    OrganismFactory factory{};

    SECTION("printAncestorHistory does not crash") {
        auto org1 = factory.createWolf();
        org1->setLineageInfo(LineageInfo(1));

        auto org2 = factory.createWolf();
        org2->setLineageInfo(LineageInfo(2, org1));

        // Print should not throw or crash
        REQUIRE_NOTHROW(LineageService::printAncestorHistory(*org2));
    }
}

