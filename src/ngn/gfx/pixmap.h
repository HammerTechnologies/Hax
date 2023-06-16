#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "../mth/vec2.h"
#include "color.h"

struct Pixmap {
	using iterator = color_t*;
	using const_iterator = const color_t*;

	Pixmap(const Vec2<uint16_t>& size, color_t color) noexcept;

	constexpr const Vec2<uint16_t>& size() const noexcept { return m_size; }
	color_t pixel(const Vec2<uint16_t>& position) const noexcept { return m_data[position.y()*m_size.x() + position.x()]; }
	void pixel(const Vec2<uint16_t>& position, color_t color) noexcept { m_data[position.y()*m_size.x() + position.x()] = color; }

	const color_t* data() const noexcept { return m_data.data(); }
	color_t* data() noexcept { return m_data.data(); }

	const_iterator cbegin() const noexcept { return data(); }
	const_iterator cend() const noexcept { return data() + m_data.size(); }
	iterator begin() noexcept { return data(); }
	iterator end() noexcept { return data() + m_data.size(); }
private:
	std::vector<color_t> m_data;
	Vec2<uint16_t> m_size;

	Pixmap(const std::string& filename) noexcept;

	friend struct Graphics;
	friend class std::default_delete<Pixmap>;
};
