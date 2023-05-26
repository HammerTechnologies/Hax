#include <memory>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"

Texture::Texture(uint16_t width, uint16_t height) noexcept
: m_id{0}, m_width{width}, m_height{height} {
	genTexture();
	setPixels(nullptr);
}

Texture::Texture(const std::string& filename) noexcept
: m_id{0}, m_width{0}, m_height{0} {
	int32_t w, h;
	const auto pixels = std::unique_ptr<uint32_t, void(*)(void*)>{
		reinterpret_cast<uint32_t*>(stbi_load(filename.c_str(), &w, &h, nullptr, 4)),
		stbi_image_free
	};
	if (!pixels) return;

	m_width = static_cast<uint16_t>(w);
	m_height = static_cast<uint16_t>(h);
	genTexture();
	setPixels(pixels.get());
}

Texture::~Texture() noexcept {
	glDeleteTextures(1, &m_id);
}

void Texture::bind() const noexcept {
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::setPixels(const uint32_t* pixels) noexcept {
	bind();
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		m_width,
		m_height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pixels);
}

void Texture::genTexture() noexcept {
	glGenTextures(1, &m_id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
