#include <string>
#include <utility>
#include "../logger.h"
#include "font.h"
#include "graphics.h"
#include "internal/graphics_driver.h"
#include "level.h"
#include "pixmap.h"
#include "texture.h"
#include "viewer.h"

constexpr const char* VERTEX_SHADER = R"VS(
uniform mat4 mvp;
uniform mat4 textureMatrix;

attribute vec3 vertexPos;
attribute vec4 vertexColor;
attribute vec2 vertexTexCoords;

varying vec4 fragColor;
varying vec2 fragTexCoords;

void main() {
	gl_Position = mvp * vec4(vertexPos, 1);
	fragColor = vertexColor;
	fragTexCoords = vec2(textureMatrix * vec4(vertexTexCoords, 0, 1));
}
)VS";

constexpr const char* FRAGMENT_SHADER = R"FS(
uniform vec4 baseColor;
uniform bool useTexture;
uniform sampler2D texture;

varying vec4 fragColor;
varying vec2 fragTexCoords;

void main() {
	if (useTexture) {
		gl_FragColor = baseColor * fragColor * texture2D(texture, fragTexCoords);
	} else {
		gl_FragColor = baseColor * fragColor;
	}
}
)FS";

Graphics::Graphics(const GraphicsDriver& driver, const Logger& logger) noexcept
: m_driver{driver},
	m_logger{logger},
	m_shader{m_driver, VERTEX_SHADER, FRAGMENT_SHADER},
	m_rect{
		m_driver,
		{
			Vertex(Vec3r(static_cast<real_t>(-0.5), static_cast<real_t>(-0.5), 0), Color::WHITE, 0, 0),
			Vertex(Vec3r(static_cast<real_t>( 0.5), static_cast<real_t>(-0.5), 0), Color::WHITE, 1, 0),
			Vertex(Vec3r(static_cast<real_t>( 0.5), static_cast<real_t>( 0.5), 0), Color::WHITE, 1, 1),
			Vertex(Vec3r(static_cast<real_t>(-0.5), static_cast<real_t>( 0.5), 0), Color::WHITE, 0, 1)},
		{0, 1, 2, 3}},
	m_quad{
		m_driver,
		{
			Vertex(Vec3r(0, 1, 0), Color::WHITE, 0, 0),
			Vertex(Vec3r(1, 1, 0), Color::WHITE, 1, 0),
			Vertex(Vec3r(1, 0, 0), Color::WHITE, 1, 1),
			Vertex(Vec3r(0, 0, 0), Color::WHITE, 0, 1)},
		{0, 1, 2, 3}},
	m_mvpLoc{m_shader.getUniform("mvp")},
	m_textureMatrixLoc{m_shader.getUniform("textureMatrix")},
	m_baseColorLoc{m_shader.getUniform("baseColor")},
	m_useTextureLoc{m_shader.getUniform("useTexture")},
	m_textureLoc{m_shader.getUniform("texture")},
	m_projection{} {
	m_logger.info("Graphics initialized.");
}

Graphics::~Graphics() noexcept {
	m_logger.info("Graphics deinitialized.");
}

std::unique_ptr<Font> Graphics::loadFont(const std::string& filename, real_t height) const noexcept {
	auto font = std::unique_ptr<Font> {new Font {filename, height, m_driver}};
	if (!font->isValid()) {
		m_logger.error("Could not load font '" + filename + "'.");
		font.reset();
	}
	return font;
}

std::unique_ptr<Pixmap> Graphics::loadPixmap(const std::string& filename) const noexcept {
	auto pixmap = std::unique_ptr<Pixmap> {new Pixmap {filename}};
	if (pixmap->getWidth() == 0 && pixmap->getHeight() == 0) {
		m_logger.error("Could not load pixmap '" + filename + "'.");
		pixmap.reset();
	}
	return pixmap;
}

std::unique_ptr<Texture> Graphics::loadTexture(const std::string& filename) const noexcept {
	auto pixmap = Pixmap {filename};
	auto texture = std::unique_ptr<Texture> {new Texture {pixmap.getWidth(), pixmap.getHeight(), m_driver}};
	if (!texture->isValid()) {
		m_logger.error("Could not load texture '" + filename + "'.");
		texture.reset();
	} else {
		texture->setPixels(pixmap.data());
	}
	return texture;
}

std::unique_ptr<Texture> Graphics::createTexture(uint16_t width, uint16_t height) const noexcept {
	return std::unique_ptr<Texture> {new Texture {width, height, m_driver}};
}

void Graphics::setup2D(uint16_t x, uint16_t y, uint16_t w, uint16_t h) noexcept {
	m_driver.setup2D(x, y, w, h);
	m_projection = Mat4r::ortho(0, w - x, h - y, 0, 0, 1);
}

void Graphics::setup3D(const Viewer& viewer) noexcept {
	m_driver.setup3D(viewer);
	m_projection =
		Mat4r::perspective(
			deg2rad(viewer.m_fov),
			static_cast<real_t>(viewer.m_viewportWidth) / viewer.m_viewportHeight,
			viewer.m_rangeMin,
			viewer.m_rangeMax)
		* viewer.getViewMatrix();
}

void Graphics::cls(uint32_t color) const noexcept {
	m_driver.cls(color);
}

void Graphics::drawRect(
	real_t x,
	real_t y,
	real_t width,
	real_t height,
	uint32_t color) const noexcept {
	const auto transform = Mat4r::transform(
		{x + width / 2, y + height / 2, 0},
		{},
		{width, height, 1});
	m_rect.bind();
	prepareShader(transform, {}, color, false);
	m_rect.draw();
}

void Graphics::drawTexture(
	const Texture* tex,
	real_t x,
	real_t y,
	real_t width,
	real_t height,
	real_t angle,
	uint32_t color,
	const Mat4r& textureMatrix) const noexcept {
	if (tex) {
		const auto realWidth = real_t {(width != 0) ? width : tex->getWidth()};
		const auto realHeight = real_t {(height != 0) ? height : tex->getHeight()};
		const auto transform = Mat4r::transform(
			{x + realWidth / 2, y + realHeight / 2, 0},
			Quatr::fromAxis(deg2rad(angle), Vec3r{0, 0, 1}),
			{realWidth, realHeight, 1});
		tex->bind();
		m_rect.bind();
		prepareShader(transform, textureMatrix, color, true);
		m_rect.draw();
	}
}

void Graphics::drawText(
	const Font* font,
	const std::string& text,
	real_t x,
	real_t y,
	uint32_t color) const noexcept {
	if (font) {
		y += font->m_maxHeight;
		for (auto i = size_t {0}; i < text.size(); ++i) {
			const auto quad = font->getFontQuad(text[i], x, y);
			const auto texMatrix = Mat4r::transform(
				{quad.m_u, quad.m_v, 0},
				{},
				{quad.m_us, quad.m_vs, 1}
			);
			drawTexture(font->m_tex.get(), quad.m_x, quad.m_y, quad.m_width, quad.m_height, 0, color, texMatrix);
		}
	}
}

void Graphics::drawQuad(const Mat4r& transform, uint32_t color) const noexcept {
	m_quad.bind();
	prepareShader(transform, Mat4r{}, color, false);
	m_quad.draw();
}

void Graphics::drawLevel2D(
	const Level& level,
	real_t x,
	real_t y,
	real_t size,
	uint32_t color) const noexcept {
	level.draw2D(*this, x, y, size, color);
}

void Graphics::drawLevel3D(const Level& level, real_t size, uint32_t color) const noexcept {
	level.draw3D(*this, size, color);
}

void Graphics::prepareShader(
	const Mat4r& transform,
	const Mat4r& textureMatrix,
	uint32_t color,
	bool useTexture) const noexcept {
	m_shader.prepare();
	m_shader.setInt(m_useTextureLoc, useTexture);
	m_shader.setInt(m_textureLoc, 0);
	m_shader.setMat4(m_mvpLoc, m_projection * transform);
	m_shader.setMat4(m_textureMatrixLoc, textureMatrix);
	m_shader.setVec4(
		m_baseColorLoc,
		Color::redf(color),
		Color::greenf(color),
		Color::bluef(color),
		Color::alphaf(color));
}
