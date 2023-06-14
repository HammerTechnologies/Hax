#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

struct Pixmap {
	using iterator = uint32_t*;
	using const_iterator = const uint32_t*;

	Pixmap(uint16_t width, uint16_t height, uint32_t color) noexcept;

	constexpr uint16_t getWidth() const noexcept { return m_width; }
	constexpr uint16_t getHeight() const noexcept { return m_height; }
	uint32_t getPixel(uint16_t x, uint16_t y) const noexcept { return m_data[y*m_width + x]; }
	void setPixel(uint16_t x, uint16_t y, uint32_t color) noexcept { m_data[y*m_width + x] = color; }

	const uint32_t* data() const noexcept { return m_data.data(); }
	uint32_t* data() noexcept { return m_data.data(); }

	const_iterator cbegin() const noexcept { return data(); }
	const_iterator cend() const noexcept { return data() + m_data.size(); }
	iterator begin() noexcept { return data(); }
	iterator end() noexcept { return data() + m_data.size(); }
private:
	std::vector<uint32_t> m_data;
	uint16_t m_width;
	uint16_t m_height;

	Pixmap(const std::string& filename) noexcept;

	friend struct Graphics;
	friend class std::default_delete<Pixmap>;
};
