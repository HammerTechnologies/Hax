#include "texture.h"

Texture::Texture(const Vec2<uint16_t>& size, const GraphicsDriver& driver) noexcept
: m_driver{driver}, m_internal{driver.createTexture()}, m_size{size} {
	pixels(nullptr);
}

Texture::~Texture() noexcept {
	m_driver.deleteTexture(m_internal);
}

void Texture::bind() const noexcept {
	m_driver.bindTexture(m_internal);
}

void Texture::pixels(const color_t* pixels) const noexcept {
	m_driver.setTexturePixels(m_internal, m_size, pixels);
}
