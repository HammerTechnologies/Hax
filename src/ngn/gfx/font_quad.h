#pragma once

#include "../mth/vec2.h"

namespace ngn {

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

} // namespace ngn
