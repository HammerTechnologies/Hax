#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include "../mth/mat4.h"
#include "../mth/real.h"
#include "../_prv/geom.h"
#include "../_prv/shader.h"
#include "color.h"

namespace ngn {

struct Font;
struct Logger;
struct Pixmap;
struct Texture;
struct Viewer;

namespace prv {
	struct GraphicsDriver;
}

struct Graphics {
	Graphics(const prv::GraphicsDriver& driver, const Logger& logger) noexcept;
	~Graphics() noexcept;

	operator bool() const noexcept { return m_driver && m_shader; }

	std::unique_ptr<Font> loadFont(const std::string& filename, real_t height) const noexcept;
	std::unique_ptr<Pixmap> loadPixmap(const std::string& filename) const noexcept;
	std::unique_ptr<Texture> loadTexture(const std::string& filename) const noexcept;
	std::unique_ptr<Texture> createTexture(uint16_t width, uint16_t height) const noexcept;

	void setup2D(const Vec2<uint16_t>& position, const Vec2<uint16_t> size) noexcept;
	void setup3D(const Viewer& viewer) noexcept;
	void cls(color_t color = Color::BLACK) const noexcept;
	void drawRect(
		const Vec2r& position,
		const Vec2r& size,
		color_t color = Color::WHITE) const noexcept;
	void drawTexture(
		const Texture* tex,
		const Vec2r& position,
		const Vec2r& size = {},
		real_t angle = 0,
		color_t color = Color::WHITE,
		const Mat4r& textureMatrix = Mat4r{}) const noexcept;
	void drawText(
		const Font* font,
		const std::string& text,
		const Vec2r& position,
		color_t color = Color::WHITE) const noexcept;
	void drawQuad(const Mat4r& transform, color_t color = Color::WHITE) const noexcept;
private:
	const prv::GraphicsDriver& m_driver;
	const Logger& m_logger;
	prv::Shader m_shader;
	prv::Geom m_rect;
	prv::Geom m_quad;
	int32_t m_mvpLoc;
	int32_t m_textureMatrixLoc;
	int32_t m_baseColorLoc;
	int32_t m_useTextureLoc;
	int32_t m_textureLoc;
	Mat4r m_projection;

	void prepareShader(
		const Mat4r& transform,
		const Mat4r& textureMatrix,
		color_t color,
		bool useTexture) const noexcept;
};

} // namespace ngn
