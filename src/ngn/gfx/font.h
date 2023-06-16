#pragma once

#include <array>
#include <memory>
#include <string>
#include <stb_truetype.h>
#include "../mth/vec2.h"
#include "../mth/real.h"
#include "_internal/graphics_driver.h"
#include "font_quad.h"

struct Texture;

struct Font {
	constexpr real_t height() const noexcept { return m_height; }
	Vec2r textSize(const std::string& text) const noexcept;
private:
	std::unique_ptr<Texture> m_tex;
	std::array<stbtt_bakedchar, 94> m_glyphs;
	real_t m_height;
	real_t m_maxHeight;

	Font(const std::string& filename, real_t height, const GraphicsDriver& driver) noexcept;
	FontQuad fontQuad(char c, Vec2r& startPos) const noexcept;

	bool isValid() const { return m_tex != nullptr; }

	friend struct Graphics;
	friend class std::default_delete<Font>;
};
