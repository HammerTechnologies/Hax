#pragma once

#include <cstdint>
#include "../../math/vec3.h"
#include "../../real.h"

struct Vertex {
	Vec3r m_position;
	uint32_t m_color;
	real_t m_texCoords[2];

	constexpr Vertex(const Vec3r& position, uint32_t color, real_t u, real_t v) noexcept
	: m_position{position}, m_color{color}, m_texCoords{u, v} {}
};
