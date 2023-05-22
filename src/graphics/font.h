#pragma once

#include <array>
#include <memory>
#include <string>
#include <stb_truetype.h>
#include "../real.h"
#include "font_quad.h"
#include "texture.h"

struct Font {
	Font(const std::string& filename, real_t height) noexcept;

	bool isValid() const { return m_tex && m_tex->isValid(); }

	constexpr real_t getHeight() const noexcept { return m_height; }
	real_t getTextWidth(const std::string& text) const noexcept;
	real_t getTextHeight(const std::string& text) const noexcept;
private:
	std::unique_ptr<Texture> m_tex;
	std::array<stbtt_bakedchar, 94> m_glyphs;
	real_t m_height;
	real_t m_maxHeight;

	FontQuad getFontQuad(char c, real_t& startX, real_t& startY) const noexcept;

	friend struct Graphics;
};
