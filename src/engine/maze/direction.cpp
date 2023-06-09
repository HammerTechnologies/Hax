#include "direction.h"

Direction getDirectionOpposite(Direction direction) {
	Direction opposite = static_cast<Direction>(
			(static_cast<uint8_t>(direction) + OPPOSITE) % DIRECTIONS);
	return opposite;
}
