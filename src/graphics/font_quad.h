#pragma once

#include "../real.h"

struct FontQuad {
	real_t m_x;
	real_t m_y;
	real_t m_width;
	real_t m_height;
	real_t m_u;
	real_t m_v;
	real_t m_us;
	real_t m_vs;

	constexpr FontQuad(
		real_t x,
		real_t y,
		real_t width,
		real_t height,
		real_t u,
		real_t v,
		real_t us,
		real_t vs) noexcept
	: m_x{x},
		m_y{y},
		m_width{width},
		m_height{height},
		m_u{u},
		m_v{v},
		m_us{us},
		m_vs{vs} {}
};
