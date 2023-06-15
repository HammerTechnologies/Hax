#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include "internal/graphics_driver.h"

struct Texture {
	constexpr uint16_t getWidth() const noexcept { return m_width; }
	constexpr uint16_t getHeight() const noexcept { return m_height; }

	void bind() const noexcept;
	void setPixels(const uint32_t* pixels) const noexcept;
private:
	const GraphicsDriver& m_driver;
	DriverTexture m_internal;
	uint16_t m_width;
	uint16_t m_height;

	Texture(uint16_t width, uint16_t height, const GraphicsDriver& driver) noexcept;
	~Texture() noexcept;

	constexpr bool isValid() const { return m_width != 0 && m_height != 0 && m_internal; }

	friend struct Font;
	friend struct Graphics;
	friend class std::default_delete<Texture>;
};