#include <memory>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"

Texture::Texture(const std::string& filename) noexcept
: m_id{0}, m_width{0}, m_height{0} {
	int w, h;
	stbi_set_flip_vertically_on_load(true);
	const auto pixels = std::unique_ptr<unsigned char, void(*)(void*)>{
		stbi_load(filename.c_str(), &w, &h, nullptr, 4),
		stbi_image_free
	};
	if (!pixels) return;

	glGenTextures(1, &m_id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		w,
		h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pixels.get());
	m_width = static_cast<uint16_t>(w);
	m_height = static_cast<uint16_t>(h);
}

Texture::~Texture() noexcept {
	glDeleteTextures(1, &m_id);
}

void Texture::bind() const noexcept {
	glBindTexture(GL_TEXTURE_2D, m_id);
}
