#pragma once

enum class SpeciesCodes {
    Unknown,
    Animal,
    Plant,
    Wolf,
    Sheep,
    Grass,
    Dandelion,
    Toadstool
};

inline constexpr const char* speciesCodeToSymbol(SpeciesCodes code) {
    switch (code) {
        case SpeciesCodes::Animal:
            return "A";
        case SpeciesCodes::Plant:
            return "P";
        case SpeciesCodes::Wolf:
            return "W";
        case SpeciesCodes::Sheep:
            return "S";
        case SpeciesCodes::Grass:
            return "G";
        case SpeciesCodes::Dandelion:
            return "D";
        case SpeciesCodes::Toadstool:
            return "T";
        case SpeciesCodes::Unknown:
        default:
            return "O";
    }
}