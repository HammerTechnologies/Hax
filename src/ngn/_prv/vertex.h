#pragma once

#include <array>
#include <cstdint>
#include "../mth/vec2.h"
#include "../mth/vec3.h"
#include "../mth/real.h"

namespace ngn::prv {

struct Vertex {
	Vec3r m_position;
	color_t m_color;
	Vec2r m_texCoords;

	constexpr Vertex(const Vec3r& position, color_t color, const Vec2r& texCoords) noexcept
	: m_position{position}, m_color{color}, m_texCoords{texCoords} {}
};

} // namespace ngn::prv
