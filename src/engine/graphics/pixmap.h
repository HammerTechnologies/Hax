#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "../math/vec2.h"

struct Pixmap {
	using iterator = uint32_t*;
	using const_iterator = const uint32_t*;

	Pixmap(const Vec2<uint16_t>& size, uint32_t color) noexcept;

	constexpr const Vec2<uint16_t>& getSize() const noexcept { return m_size; }
	uint32_t getPixel(const Vec2<uint16_t>& position) const noexcept { return m_data[position.y()*m_size.x() + position.x()]; }
	void setPixel(const Vec2<uint16_t>& position, uint32_t color) noexcept { m_data[position.y()*m_size.x() + position.x()] = color; }

	const uint32_t* data() const noexcept { return m_data.data(); }
	uint32_t* data() noexcept { return m_data.data(); }

	const_iterator cbegin() const noexcept { return data(); }
	const_iterator cend() const noexcept { return data() + m_data.size(); }
	iterator begin() noexcept { return data(); }
	iterator end() noexcept { return data() + m_data.size(); }
private:
	std::vector<uint32_t> m_data;
	Vec2<uint16_t> m_size;

	Pixmap(const std::string& filename) noexcept;

	friend struct Graphics;
	friend class std::default_delete<Pixmap>;
};
