#pragma once

#include <memory>

class Organism;

struct LineageInfo {
        int birthTurn{ 0 };
        int deathTurn{ -1 };
        std::shared_ptr<Organism> parent{ nullptr };

        LineageInfo() = default;

        LineageInfo(int birthTurn, std::shared_ptr<Organism> parent = nullptr);
};