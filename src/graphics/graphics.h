#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include "../math/mat4.h"
#include "../real.h"
#include "color.h"
#include "internal/geom.h"
#include "internal/shader.h"

struct Font;
struct GraphicsDriver;
struct Logger;
struct Texture;
struct Viewer;

struct Graphics {
	Graphics(const GraphicsDriver& driver, const Logger& logger) noexcept;
	~Graphics() noexcept;

	operator bool() const noexcept { return m_driver && m_shader; }

	std::unique_ptr<Font> loadFont(const std::string& filename, real_t height) const noexcept;
	std::unique_ptr<Texture> loadTexture(const std::string& filename) const noexcept;
	std::unique_ptr<Texture> createTexture(uint16_t width, uint16_t height) const noexcept;

	void setup2D(uint16_t x, uint16_t y, uint16_t w, uint16_t h) noexcept;
	void setup3D(const Viewer& viewer) noexcept;
	void cls(uint32_t color = Color::BLACK) const noexcept;
	void drawRect(
		real_t x,
		real_t y,
		real_t width,
		real_t height,
		uint32_t color = Color::WHITE) const noexcept;
	void drawTexture(
		const Texture& tex,
		real_t x,
		real_t y,
		real_t width = 0,
		real_t height = 0,
		real_t angle = 0,
		uint32_t color = Color::WHITE,
		const Mat4r& textureMatrix = Mat4r{}) const noexcept;
	void drawText(
		const Font& font,
		const std::string& text,
		real_t x,
		real_t y,
		uint32_t color = Color::WHITE) const noexcept;
	void drawQuad(const Mat4r& transform, uint32_t color = Color::WHITE) const noexcept;
private:
	const GraphicsDriver& m_driver;
	const Logger& m_logger;
	Shader m_shader;
	Geom m_rect;
	int32_t m_mvpLoc;
	int32_t m_textureMatrixLoc;
	int32_t m_baseColorLoc;
	int32_t m_useTextureLoc;
	int32_t m_textureLoc;
	Mat4r m_projection;

	void prepareShader(
		const Mat4r& transform,
		const Mat4r& textureMatrix,
		uint32_t color,
		bool useTexture) const noexcept;
};
