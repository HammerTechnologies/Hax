#pragma once

#include <array>
#include <memory>
#include <string>
#include <stb_truetype.h>
#include "../real.h"
#include "font_quad.h"
#include "internal/graphics_driver.h"

struct Texture;

struct Font {
	constexpr real_t getHeight() const noexcept { return m_height; }
	real_t getTextWidth(const std::string& text) const noexcept;
	real_t getTextHeight(const std::string& text) const noexcept;
private:
	std::unique_ptr<Texture> m_tex;
	std::array<stbtt_bakedchar, 94> m_glyphs;
	real_t m_height;
	real_t m_maxHeight;

	Font(const std::string& filename, real_t height, const GraphicsDriver& driver) noexcept;
	FontQuad getFontQuad(char c, real_t& startX, real_t& startY) const noexcept;

	bool isValid() const { return m_tex != nullptr; }

	friend struct Graphics;
	friend class std::default_delete<Font>;
};
