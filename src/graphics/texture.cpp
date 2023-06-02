#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"

Texture::Texture(uint16_t width, uint16_t height, const GraphicsDriver& driver) noexcept
: m_driver{driver}, m_internal{driver.createTexture()}, m_width{width}, m_height{height} {
	setPixels(nullptr);
}

Texture::Texture(const std::string& filename, const GraphicsDriver& driver) noexcept
: m_driver{driver}, m_internal{driver.createTexture()}, m_width{0}, m_height{0} {
	int32_t w, h;
	const auto pixels = std::unique_ptr<uint32_t, void(*)(void*)>{
		reinterpret_cast<uint32_t*>(stbi_load(filename.c_str(), &w, &h, nullptr, 4)),
		stbi_image_free
	};
	if (!pixels) return;

	m_width = static_cast<uint16_t>(w);
	m_height = static_cast<uint16_t>(h);
	setPixels(pixels.get());
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
