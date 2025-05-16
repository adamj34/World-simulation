#pragma once
#include <string>

namespace validators {

void validateValueNotNegative(int x, const std::string& object = "Value");
void validateDimension(int startWorldX, int worldX);

} // namespace validators