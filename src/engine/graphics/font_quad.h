#pragma once

#include "../math/vec2.h"

struct FontQuad {
	Vec2r m_position;
	Vec2r m_size;
	Vec2r m_tex;
	Vec2r m_texSize;

	constexpr FontQuad(
		const Vec2r& position,
		const Vec2r& size,
		const Vec2r& tex,
		const Vec2r& texSize) noexcept
	: m_position {position},
		m_size {size},
		m_tex {tex},
		m_texSize {texSize} {}
};
