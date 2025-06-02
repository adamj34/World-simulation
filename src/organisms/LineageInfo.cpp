#include "organisms/LineageInfo.hpp"

LineageInfo::LineageInfo(int birthTurn, std::shared_ptr<Organism> parent)
    : birthTurn(birthTurn)
    , parent(std::move(parent)) {
}