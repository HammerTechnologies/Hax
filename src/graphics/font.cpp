#include <algorithm>
#include <fstream>
#include <vector>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#undef STB_TRUETYPE_IMPLEMENTATION
#include "font.h"

Font::Font(const std::string& filename, real_t height, const GraphicsDriver& driver) noexcept
: m_tex{nullptr} {
	// Read file into buffer
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open()) return;
	std::vector<uint8_t> ttf(static_cast<size_t>(file.tellg()));
	file.seekg(0);
	file.read(reinterpret_cast<char*>(ttf.data()), ttf.size());
	file.close();

	// Bake font into alpha buffer
	uint16_t w = 64, h = 64;
	std::vector<uint8_t> alphaBuffer(w * h);
	while (stbtt_BakeFontBitmap(ttf.data(), 0, height, alphaBuffer.data(), w, h, 32, m_glyphs.size(), m_glyphs.data()) <= 0) {
		if (w == h) {
			w *= 2;
		} else {
			h *= 2;
		}
		alphaBuffer.resize(w * h);
	}
	ttf.clear();

	// Copy into pixels
	std::vector<uint8_t> pixels(w * h * 4, 255);
	for (size_t i = 0; i < w*h; ++i) {
		pixels[i*4 + 3] = alphaBuffer[i];
	}
	alphaBuffer.clear();

	// Create texture
	m_tex = std::unique_ptr<Texture>(new Texture(w, h, driver));
	m_tex->setPixels(reinterpret_cast<uint32_t*>(pixels.data()));
	pixels.clear();

	// Get max char height
	real_t x = 0, y = 0;
	real_t miny = 999999, maxy = -999999;
	stbtt_aligned_quad q;
	m_maxHeight = -999999;
	const size_t len = m_glyphs.size();
	for (size_t i = 0; i < len; ++i) {
		stbtt_GetBakedQuad(m_glyphs.data(), m_tex->getWidth(), m_tex->getHeight(), i, &x, &y, &q, true);
		miny = std::min(miny, q.y0);
		maxy = std::max(maxy, q.y1);
	}
	m_maxHeight = maxy - miny;
}

real_t Font::getTextWidth(const std::string& text) const noexcept {
	real_t x = 0, y = 0;
	stbtt_aligned_quad q;
	memset(&q, 0, sizeof(q));
	for (size_t i = 0; i < text.size(); ++i) {
		stbtt_GetBakedQuad(m_glyphs.data(), m_tex->getWidth(), m_tex->getHeight(), std::min(text[i] - 32, 94), &x, &y, &q, true);
	}
	return q.x1;
}

real_t Font::getTextHeight(const std::string& text) const noexcept {
	real_t x = 0, y = 0, miny = 999999, maxy = -999999;
	stbtt_aligned_quad q;
	memset(&q, 0, sizeof(q));
	for (size_t i = 0; i < text.length(); ++i) {
		stbtt_GetBakedQuad(m_glyphs.data(), m_tex->getWidth(), m_tex->getHeight(), std::min(text[i] - 32, 94), &x, &y, &q, true);
		miny = std::min(miny, q.y0);
		maxy = std::max(maxy, q.y1);
	}
	return maxy - miny;
}

FontQuad Font::getFontQuad(char c, real_t& startX, real_t& startY) const noexcept {
	stbtt_aligned_quad q;
	stbtt_GetBakedQuad(
		m_glyphs.data(),
		m_tex->getWidth(),
		m_tex->getHeight(),
		std::min(c - 32, 94),
		&startX,
		&startY,
		&q,
		true);
	return FontQuad{q.x0, q.y0, q.x1 - q.x0, q.y1 - q.y0, q.s0, q.t0, q.s1 - q.s0, q.t1 - q.t0};
}
