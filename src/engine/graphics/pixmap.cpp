#include <algorithm>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "pixmap.h"

Pixmap::Pixmap(uint16_t width, uint16_t height, uint32_t color) noexcept
: m_data(width * height), m_width{width}, m_height{height} {
	std::fill(m_data.begin(), m_data.end(), color);
}

Pixmap::Pixmap(const std::string& filename) noexcept
: m_data{}, m_width{0}, m_height{0} {
	auto w = 0, h = 0;
	const auto pixels = std::unique_ptr<uint32_t, void(*)(void*)>{
		reinterpret_cast<uint32_t*>(stbi_load(filename.c_str(), &w, &h, nullptr, 4)),
		stbi_image_free
	};
	if (!pixels) return;

	m_width = uint16_t(w);
	m_height = uint16_t(h);
	m_data.resize(w * h);
	std::copy(pixels.get(), pixels.get() + m_data.size(), m_data.begin());
}
