#pragma once

#include "color.h"
#include "../mth/vec2.h"
#include "../mth/vec3.h"
#include "../mth/real.h"

namespace ngn {

struct Vertex {
	Vec3r position;
	color_t color;
	Vec2r texCoords;

	constexpr Vertex(const Vec3r& position, color_t color, const Vec2r& texCoords) noexcept
	: position{position}, color{color}, texCoords{texCoords} {}
};

} // namespace ngn
