#include "organisms/OrganismFactory.hpp"
#include "organisms/Dandelion.hpp"
#include "organisms/Grass.hpp"
#include "organisms/Sheep.hpp"
#include "organisms/Toadstool.hpp"
#include "organisms/Wolf.hpp"

std::shared_ptr<Organism> OrganismFactory::createWolf(Position position) const {
    return std::make_shared<Wolf>(std::move(position));
}

std::shared_ptr<Organism> OrganismFactory::createSheep(Position position) const {
    return std::make_shared<Sheep>(std::move(position));
}

std::shared_ptr<Organism> OrganismFactory::createGrass(Position position) const {
    return std::make_shared<Grass>(std::move(position));
}

std::shared_ptr<Organism> OrganismFactory::createDandelion(Position position) const {
    return std::make_shared<Dandelion>(std::move(position));
}

std::shared_ptr<Organism> OrganismFactory::createToadstool(Position position) const {
    return std::make_shared<Toadstool>(std::move(position));
}