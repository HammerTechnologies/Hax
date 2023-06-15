#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include "../math/vec2.h"
#include "internal/graphics_driver.h"

struct Texture {
	constexpr const Vec2<uint16_t>& getSize() const noexcept { return m_size; }

	void bind() const noexcept;
	void setPixels(const uint32_t* pixels) const noexcept;
private:
	const GraphicsDriver& m_driver;
	DriverTexture m_internal;
	Vec2<uint16_t> m_size;

	Texture(const Vec2<uint16_t>& size, const GraphicsDriver& driver) noexcept;
	~Texture() noexcept;

	constexpr bool isValid() const { return m_size != Vec2<uint16_t> {0, 0} && m_internal; }

	friend struct Font;
	friend struct Graphics;
	friend class std::default_delete<Texture>;
};
