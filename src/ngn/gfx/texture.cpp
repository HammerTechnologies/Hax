#include "texture.h"

namespace ngn {

Texture::Texture(const Vec2<uint16_t>& size, const prv::GraphicsDriver& driver) noexcept
: m_driver{driver}, m_internal{driver.createTexture()}, m_size{size} {
	pixels(nullptr);
}

void Texture::bind() const noexcept {
	m_driver.bindTexture(*m_internal);
}

void Texture::pixels(non_owning_ptr<const color_t> pixels) const noexcept {
	m_driver.setTexturePixels(*m_internal, m_size, pixels);
}

} // namespace ngn
