#pragma once

#include "ISimulationWorld.hpp"
#include <cstdint>
#include <random>

class Simulator {
    private:
        ISimulationWorld& m_world;
        int m_turn{ 0 };
        std::mt19937 m_rng{ std::random_device{}() };

        int pickRandomPosition(const std::vector<Position>& positions);
        void applyTurnRules();

        void playTurnForOrganism(const std::shared_ptr<Organism>& organism);

        void performAttack(const std::shared_ptr<Organism>& organism);
        void performReproduction(const std::shared_ptr<Organism>& organism, const std::vector<Position>& freePositions);
        void performMove(const std::shared_ptr<Organism>& organism, const std::vector<Position>& freePositions);


    public:
        explicit Simulator(ISimulationWorld& world);
        Simulator(ISimulationWorld& world, std::uint32_t seed);

        int getTurn() const;
        void setTurn(int turn);

        void playTurn();

        void runSimulation(int numberOfTurns = 5);
};