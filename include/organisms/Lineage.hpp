#pragma once

#include <memory>
#include <vector>

class Organism;

struct LineageInfo {
    int birthTurn{ 0 };
    int deathTurn{ -1 };
    std::shared_ptr<Organism> parent{ nullptr };

    LineageInfo() = default;

    LineageInfo(int birthTurn, std::shared_ptr<Organism> parent = nullptr);
};

class LineageService {
    public:
        static std::vector<std::shared_ptr<Organism>> getAncestorHistory(const Organism& organism);
        static void printAncestorHistory(const Organism& organism); 
};