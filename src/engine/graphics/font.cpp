#include <algorithm>
#include <fstream>
#include <vector>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#undef STB_TRUETYPE_IMPLEMENTATION
#include "font.h"
#include "texture.h"

Font::Font(const std::string& filename, real_t height, const GraphicsDriver& driver) noexcept {
	// Read file into buffer
	auto file = std::ifstream {filename, std::ios::ate | std::ios::binary};
	if (!file.is_open()) return;
	auto ttf = std::vector<colorcomp_t>(file.tellg());
	file.seekg(0);
	file.read(reinterpret_cast<char*>(ttf.data()), ttf.size());
	file.close();

	// Bake font into alpha buffer
	auto w = 64, h = 64;
	auto alphaBuffer = std::vector<colorcomp_t>(w * h);
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
	auto pixels = std::vector<colorcomp_t>(w * h * 4, 255);
	for (auto i = 0; i < w*h; ++i) {
		pixels[i*4 + 3] = alphaBuffer[i];
	}
	alphaBuffer.clear();

	// Create texture
	m_tex = std::unique_ptr<Texture> {new Texture {Vec2<uint16_t>(w, h), driver}};
	m_tex->setPixels(reinterpret_cast<color_t*>(pixels.data()));
	pixels.clear();

	// Get max char height
	auto x = 0.f, y = 0.f;
	auto miny = 999999.f, maxy = -999999.f;
	auto q = stbtt_aligned_quad {};
	m_maxHeight = -999999;
	const auto len = m_glyphs.size();
	for (auto i = size_t {0}; i < len; ++i) {
		stbtt_GetBakedQuad(m_glyphs.data(), m_tex->getSize().x(), m_tex->getSize().y(), i, &x, &y, &q, true);
		miny = std::min(miny, q.y0);
		maxy = std::max(maxy, q.y1);
	}
	m_maxHeight = maxy - miny;
}

Vec2r Font::getTextSize(const std::string& text) const noexcept {
	auto x = 0.f, y = 0.f, miny = 999999.f, maxy = -999999.f;
	auto q = stbtt_aligned_quad {};
	for (auto i = size_t {0}; i < text.size(); ++i) {
		stbtt_GetBakedQuad(m_glyphs.data(), m_tex->getSize().x(), m_tex->getSize().y(), std::min(text[i] - 32, 94), &x, &y, &q, true);
		miny = std::min(miny, q.y0);
		maxy = std::max(maxy, q.y1);
	}
	return {q.x1, maxy - miny};
}

FontQuad Font::getFontQuad(char c, Vec2r& startPos) const noexcept {
	auto q = stbtt_aligned_quad {};
	stbtt_GetBakedQuad(
		m_glyphs.data(),
		m_tex->getSize().x(),
		m_tex->getSize().y(),
		std::min(c - 32, 94),
		&startPos.x(),
		&startPos.y(),
		&q,
		true);
	return {{q.x0, q.y0}, {q.x1 - q.x0, q.y1 - q.y0}, {q.s0, q.t0}, {q.s1 - q.s0, q.t1 - q.t0}};
}
