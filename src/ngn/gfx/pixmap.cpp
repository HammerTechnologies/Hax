#include <algorithm>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "pixmap.h"

namespace ngn {

Pixmap::Pixmap(const Vec2<uint16_t>& size, color_t color) noexcept
: m_data(size.x() * size.y()), m_size{size} {
	std::fill(m_data.begin(), m_data.end(), color);
}

Pixmap::Pixmap(const std::string& filename) noexcept
: m_data{}, m_size{0, 0} {
	auto w = 0, h = 0;
	const auto pixels = std::unique_ptr<color_t, void(*)(void*)>{
		reinterpret_cast<color_t*>(stbi_load(filename.c_str(), &w, &h, nullptr, 4)),
		stbi_image_free
	};
	if (!pixels) return;

	m_size = {uint16_t(w), uint16_t(h)};
	m_data.resize(w * h);
	std::copy(pixels.get(), pixels.get() + m_data.size(), m_data.begin());
}

} // namespace ngn
