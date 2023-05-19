#pragma once

#include <cstdint>
#include <string>
#include "../math/mat4.h"
#include "../real.h"
#include "color.h"
#include "internal/geom.h"
#include "internal/shader.h"

struct Graphics {
	Graphics() noexcept;

	constexpr bool isValid() const noexcept { return m_shader.isValid(); };
	constexpr const std::string& getError() const noexcept { return m_shader.getError(); }
	
	void setup2D(uint16_t x, uint16_t y, uint16_t w, uint16_t h) noexcept;
	void cls(uint32_t color) const noexcept;
	void drawRect(real_t x, real_t y, real_t width, real_t height, uint32_t color = Color::WHITE) const noexcept;
	/*void drawTexture(
		Texture& tex,
		real_t x,
		real_t y,
		real_t width = 0,
		real_t height = 0,
		real_t angle = 0,
		uint32_t color = Color::WHITE) noexcept;
	void drawText(Font& font, const char* text, real_t x, real_t y, uint32_t color = Color::WHITE) noexcept;*/
private:
	Shader m_shader;
	Geom m_rect;
	int32_t m_mvpLoc;
	int32_t m_baseColorLoc;
	int32_t m_useTextureLoc;
	int32_t m_textureLoc;
	Mat4r m_projection;

	void prepareShader(const Mat4r& transform, uint32_t color) const noexcept;
};
