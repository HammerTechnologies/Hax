#pragma once

#include <cstdint>

constexpr uint8_t DIRECTIONS = 4;
constexpr uint8_t OPPOSITE = 2;

enum class Direction {
	East,
	South,
	West,
	North
};

Direction getDirectionOpposite(Direction direction);
