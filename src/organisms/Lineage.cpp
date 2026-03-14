#include "organisms/Lineage.hpp"
#include "organisms/Organism.hpp"
#include <print>

LineageInfo::LineageInfo(int birthTurn, std::shared_ptr<Organism> parent)
    : birthTurn(birthTurn)
    , parent(std::move(parent)) {
}

std::vector<std::shared_ptr<Organism>> LineageService::getAncestorHistory(const Organism& firstOrganism)  {
    std::vector<std::shared_ptr<Organism>> ancestors {};
    std::shared_ptr<Organism> current = firstOrganism.getParent();
    while (current) {
        ancestors.push_back(current);
        current = current->getParent();
    }
    return ancestors;
}

void LineageService::printAncestorHistory(const Organism& organism) {
    auto ancestors{ getAncestorHistory(organism) };
    for (const auto& ancestor : ancestors) {
        std::println("Ancestor Born at turn: {}, died: {}", ancestor->getLineageInfo().birthTurn,
                     ancestor->getLineageInfo().deathTurn);
    }
}
