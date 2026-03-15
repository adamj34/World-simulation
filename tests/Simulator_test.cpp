#include "simulation/Simulator.hpp"
#include "simulation/ISimulationWorld.hpp"
#include "World.hpp"
#include "organisms/OrganismFactory.hpp"
#include <catch2/catch_test_macros.hpp>
#include <optional>


class SpyOrganism final : public Organism {
    public:
        int attackCalls{ 0 };
        int reproduceCalls{ 0 };
        int moveCalls{ 0 };
        std::vector<std::string> callTrace{};
        int lastAttackInputSize{ -1 };
        Position lastMovePosition{ 0, 0 };
        std::optional<std::shared_ptr<Organism>> attackResult{ std::nullopt };
        std::optional<std::shared_ptr<Organism>> reproduceResult{ std::nullopt };

        explicit SpyOrganism(Position position = Position{ 0, 0 })
            : Organism(std::move(position)) {
            setSpecies(SpeciesCodes::Animal);
            setSubspecies(SpeciesCodes::Wolf);
            setLiveLength(10);
            setPowerToReproduce(5);
            setPower(5);
        }

        void move(const Position& newPosition) override {
            ++moveCalls;
            callTrace.push_back("move");
            lastMovePosition = newPosition;
            setPosition(newPosition);
        }

        std::optional<std::shared_ptr<Organism>> attack(std::vector<std::shared_ptr<Organism>> organismsToAttack) override {
            ++attackCalls;
            callTrace.push_back("attack");
            lastAttackInputSize = static_cast<int>(organismsToAttack.size());
            return attackResult;
        }

        std::optional<std::shared_ptr<Organism>> reproduce() override {
            ++reproduceCalls;
            callTrace.push_back("reproduce");
            return reproduceResult;
        }

        std::shared_ptr<Organism> clone() override {
            return std::make_shared<SpyOrganism>(*this);
        }
};

class FakeSimulationWorldSpy final : public ISimulationWorld {
    private:
        std::vector<std::shared_ptr<Organism>> m_organisms{};

    public:
        bool canPlayTurn{ true };
        std::vector<Position> validPositionsAround{};
        std::vector<Position> positionsAround{};
        std::vector<std::shared_ptr<Organism>> organismsAtPosition{};
        std::vector<std::pair<std::shared_ptr<Organism>, int>> markedDead{};
        std::vector<std::shared_ptr<Organism>> addedOrganisms{};

        int toStringCalls{ 0 };
        int powerIncreaseCalls{ 0 };
        int liveLengthDecreaseCalls{ 0 };
        int removeDeadCalls{ 0 };

        void setOrganisms(std::vector<std::shared_ptr<Organism>> organisms) {
            m_organisms = std::move(organisms);
        }

        const std::vector<std::shared_ptr<Organism>>& getOrganisms() const override {
            return m_organisms;
        }

        std::vector<std::shared_ptr<Organism>> getOrganismsFromPosition(const Position&) override {
            return organismsAtPosition;
        }

        std::vector<Position> getPositionsAround(const std::shared_ptr<Organism>&) override {
            return positionsAround;
        }

        std::vector<Position> getValidPositionsAround(const std::shared_ptr<Organism>&) override {
            return validPositionsAround;
        }

        bool organismCanPlayTurn(const std::shared_ptr<Organism>&) const override {
            return canPlayTurn;
        }

        void markOrganismAsDead(const std::shared_ptr<Organism>& organism, int deathTurn) override {
            markedDead.emplace_back(organism, deathTurn);
        }

        void addOrganism(std::shared_ptr<Organism> organism) override {
            addedOrganisms.push_back(std::move(organism));
        }

        void increaseOrganismsPowerBy(int) override {
            ++powerIncreaseCalls;
        }

        void decreaseOrganismsLiveLengthBy(int) override {
            ++liveLengthDecreaseCalls;
        }

        void removeDeadOrganisms() override {
            ++removeDeadCalls;
        }

        std::string toString() override {
            ++toStringCalls;
            return {};
        }
};

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

TEST_CASE("Simulator skips organism turn when world says organism cannot play", "[Simulator]") {
    FakeSimulationWorldSpy world{};
    world.canPlayTurn = false;

    auto organism = std::make_shared<SpyOrganism>(Position{ 1, 1 });
    world.setOrganisms({ organism });

    Simulator simulator{ world, 3U };
    simulator.playTurn();

    REQUIRE(organism->attackCalls == 0);
    REQUIRE(organism->reproduceCalls == 0);
    REQUIRE(organism->moveCalls == 0);
}

TEST_CASE("Simulator executes attack, reproduce, move in order", "[Simulator]") {
    FakeSimulationWorldSpy world{};
    world.canPlayTurn = true;
    world.organismsAtPosition = { std::make_shared<SpyOrganism>(Position{ 1, 1 }) };
    world.validPositionsAround = { Position{ 2, 2 } };
    world.positionsAround = { Position{ 3, 3 } };

    auto organism = std::make_shared<SpyOrganism>(Position{ 1, 1 });
    world.setOrganisms({ organism });

    Simulator simulator{ world, 4U };
    simulator.playTurn();

    REQUIRE(organism->callTrace == std::vector<std::string>{ "attack", "reproduce", "move" });
    REQUIRE(organism->lastAttackInputSize == 1);
}

TEST_CASE("Simulator marks attacked organism as dead with current turn", "[Simulator]") {
    FakeSimulationWorldSpy world{};
    world.canPlayTurn = true;

    auto organism = std::make_shared<SpyOrganism>(Position{ 1, 1 });
    auto victim = std::make_shared<SpyOrganism>(Position{ 1, 1 });
    organism->attackResult = victim;
    world.organismsAtPosition = { victim };
    world.setOrganisms({ organism });

    Simulator simulator{ world, 5U };
    simulator.playTurn();

    REQUIRE(world.markedDead.size() == 1);
    REQUIRE(world.markedDead[0].first == victim);
    REQUIRE(world.markedDead[0].second == 0);
}

TEST_CASE("Simulator adds offspring and sets lineage data", "[Simulator]") {
    FakeSimulationWorldSpy world{};
    world.canPlayTurn = true;
    world.validPositionsAround = { Position{ 7, 7 } };

    auto parent = std::make_shared<SpyOrganism>(Position{ 2, 2 });
    auto child = std::make_shared<SpyOrganism>(Position{ 0, 0 });
    parent->reproduceResult = child;
    world.setOrganisms({ parent });

    Simulator simulator{ world, 6U };
    simulator.playTurn();

    REQUIRE(world.addedOrganisms.size() == 1);
    REQUIRE(world.addedOrganisms[0] == child);
    REQUIRE(child->getPosition() == Position{ 7, 7 });
    REQUIRE(child->getBirthTurn() == 0);
    REQUIRE(child->getParent() == parent);
}

TEST_CASE("Simulator runSimulation advances turn counter", "[Simulator]") {
    World world{ 8, 8 };
    OrganismFactory factory{};
    world.addOrganism(factory.createWolf(Position{ 4, 4 }));

    Simulator simulator{ world, 7U };
    REQUIRE(simulator.getTurn() == 0);

    simulator.runSimulation(3);

    REQUIRE(simulator.getTurn() == 3);
}

TEST_CASE("Simulator applies end-of-turn organism rules", "[Simulator]") {
    World world{ 8, 8 };
    OrganismFactory factory{};
    auto wolf = factory.createWolf(Position{ 4, 4 });
    world.addOrganism(wolf);

    const int initialPower = wolf->getPower();
    const int initialLiveLength = wolf->getLiveLength();

    Simulator simulator{ world, 11U };
    simulator.runSimulation(2);

    REQUIRE(wolf->getPower() == initialPower + 2);
    REQUIRE(wolf->getLiveLength() == initialLiveLength - 2);
}

TEST_CASE("Simulator can run against world port implementation", "[Simulator]") {
    FakeSimulationWorldSpy fakeWorld{};
    Simulator simulator{ fakeWorld, 19U };

    simulator.runSimulation(2);

    REQUIRE(simulator.getTurn() == 2);
    REQUIRE(fakeWorld.toStringCalls == 2);
    REQUIRE(fakeWorld.powerIncreaseCalls == 2);
    REQUIRE(fakeWorld.liveLengthDecreaseCalls == 2);
    REQUIRE(fakeWorld.removeDeadCalls == 2);
}
