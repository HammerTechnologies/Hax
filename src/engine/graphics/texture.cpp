#include "texture.h"

Texture::Texture(uint16_t width, uint16_t height, const GraphicsDriver& driver) noexcept
: m_driver{driver}, m_internal{driver.createTexture()}, m_width{width}, m_height{height} {
	setPixels(nullptr);
}

Texture::~Texture() noexcept {
	m_driver.deleteTexture(m_internal);
}

void Texture::bind() const noexcept {
	m_driver.bindTexture(m_internal);
}

void Texture::setPixels(const uint32_t* pixels) const noexcept {
	m_driver.setTexturePixels(m_internal, m_width, m_height, pixels);
}
