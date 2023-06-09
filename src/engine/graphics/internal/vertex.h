#pragma once

#include <array>
#include <cstdint>
#include "../../math/vec3.h"
#include "../../real.h"

struct Vertex {
	Vec3r m_position;
	uint32_t m_color;
	std::array<real_t, 2> m_texCoords;

	constexpr Vertex(const Vec3r& position, uint32_t color, real_t u, real_t v) noexcept
	: m_position{position}, m_color{color}, m_texCoords{u, v} {}
};
