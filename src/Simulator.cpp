#include "Simulator.hpp"
#include "validators.hpp"
#include "World.hpp"
#include <print>

Simulator::Simulator(ISimulationWorld& world)
    : Simulator(world, std::random_device{}()) {
}

Simulator::Simulator(ISimulationWorld& world, std::uint32_t seed)
    : m_world(world)
    , m_rng(seed) {
}

int Simulator::getTurn() const {
    return m_turn;
}
void Simulator::setTurn(int turn) {
    validators::validateValueNotNegative(turn);
    m_turn = turn;
}

int Simulator::pickRandomPosition(const std::vector<Position>& positions) {
    std::uniform_int_distribution<int> distrib(0, static_cast<int>(positions.size()) - 1);
    return distrib(m_rng);
}

void Simulator::applyTurnRules() {
    m_world.increaseOrganismsPowerBy(1);
    m_world.decreaseOrganismsLiveLengthBy(1);
    m_world.removeDeadOrganisms();
}

void Simulator::playTurnForOrganism(const std::shared_ptr<Organism>& organism) {
    if (!m_world.organismCanPlayTurn(organism)) {
        return; // Skip organisms that were already killed in this turn
    }
    
    performAttack(organism);
    auto freePositions = m_world.getValidPositionsAround(organism);
    performReproduction(organism, freePositions);
    auto adjacentPositions = m_world.getPositionsAround(organism);
    performMove(organism, adjacentPositions);
}

void Simulator::performAttack(const std::shared_ptr<Organism>& organism) {
    auto organismsAtPosition = m_world.getOrganismsFromPosition(organism->getPosition());
    if (!organismsAtPosition.empty()) {
        auto killedOrganism = organism->attack(organismsAtPosition);
        if (killedOrganism.has_value()) {
            m_world.markOrganismAsDead(killedOrganism.value(), getTurn());
        }
    }
}

void Simulator::performReproduction(const std::shared_ptr<Organism>& organism, const std::vector<Position>& freePositions) {
    auto newOrganism = organism->reproduce();
    if (newOrganism.has_value() && !freePositions.empty()) {
        int randomPositionIndex = pickRandomPosition(freePositions);
        Position newPosition = freePositions[randomPositionIndex];
        newOrganism.value()->setPosition(newPosition);
        newOrganism.value()->setLineageInfo(LineageInfo{ getTurn(), organism });

        m_world.addOrganism(newOrganism.value());
    }
}

void Simulator::performMove(const std::shared_ptr<Organism>& organism, const std::vector<Position>& freePositions) {
    if (!freePositions.empty()) {
        int randomPositionIndex = pickRandomPosition(freePositions);
        Position newPosition = freePositions[randomPositionIndex];
        organism->move(newPosition);
    }
}

void Simulator::playTurn() {
    const auto organisms = m_world.getOrganisms();
    for (const auto& organism : organisms) {
        playTurnForOrganism(organism);
    }
}

void Simulator::runSimulation(int numberOfTurns) {
    validators::validateValueNotNegative(numberOfTurns, "Number of turns");

    for (int i = 0; i < numberOfTurns; ++i) {
        std::println("Turn: {}\n{}", m_turn, m_world.toString());
        playTurn();
        applyTurnRules();
        m_turn++;
    }
}
