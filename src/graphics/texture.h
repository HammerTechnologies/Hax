#pragma once

#include <cstdint>
#include <string>

struct Texture {
	Texture(const std::string& filename) noexcept;
	~Texture() noexcept;

	constexpr bool isValid() const { return m_id != 0; }

	constexpr uint16_t getWidth() const noexcept { return m_width; }
	constexpr uint16_t getHeight() const noexcept { return m_height; }

	void bind() const noexcept;
private:
	uint32_t m_id;
	uint16_t m_width;
	uint16_t m_height;
};
