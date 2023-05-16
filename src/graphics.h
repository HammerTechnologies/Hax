#pragma once

#include "color.h"
#include "real.h"

struct Graphics {
	void setup2D(int x, int y, int w, int h) noexcept;
	void cls(uint32_t color) noexcept;
};
