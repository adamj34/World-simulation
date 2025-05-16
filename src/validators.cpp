#include "validators.hpp"
#include <stdexcept>

namespace validators {

void validateValueNotNegative(int x, const std::string& object) {
    if (x < 0) {
        throw std::invalid_argument(object + " cannot be negative. Value: " + std::to_string(x));
    }
}

void validateDimension(int startWorldX, int worldX) {
    validateValueNotNegative(startWorldX, "Start World dimension");
    if (worldX <= startWorldX) {
        throw std::invalid_argument("World dimension cannot be less than or equal to the Start World dimension");
    }
}

} // namespace validators