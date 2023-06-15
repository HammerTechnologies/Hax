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
			{{-0.5, -0.5, 0}, Color::WHITE, {0, 0}},
			{{ 0.5, -0.5, 0}, Color::WHITE, {1, 0}},
			{{ 0.5,  0.5, 0}, Color::WHITE, {1, 1}},
			{{-0.5,  0.5, 0}, Color::WHITE, {0, 1}}
		},
		{0, 1, 2, 3}},
	m_quad{
		m_driver,
		{
			{{0, 1, 0}, Color::WHITE, {0, 0}},
			{{1, 1, 0}, Color::WHITE, {1, 0}},
			{{1, 0, 0}, Color::WHITE, {1, 1}},
			{{0, 0, 0}, Color::WHITE, {0, 1}}
		},
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
	if (pixmap->size() == Vec2<uint16_t> {0, 0}) {
		m_logger.error("Could not load pixmap '" + filename + "'.");
		pixmap.reset();
	}
	return pixmap;
}

std::unique_ptr<Texture> Graphics::loadTexture(const std::string& filename) const noexcept {
	auto pixmap = Pixmap {filename};
	auto texture = std::unique_ptr<Texture> {new Texture {pixmap.size(), m_driver}};
	if (!texture->isValid()) {
		m_logger.error("Could not load texture '" + filename + "'.");
		texture.reset();
	} else {
		texture->pixels(pixmap.data());
	}
	return texture;
}

std::unique_ptr<Texture> Graphics::createTexture(uint16_t width, uint16_t height) const noexcept {
	return std::unique_ptr<Texture> {new Texture {{width, height}, m_driver}};
}

void Graphics::setup2D(const Vec2<uint16_t>& position, const Vec2<uint16_t> size) noexcept {
	m_driver.setup2D(position, size);
	m_projection = Mat4r::ortho(0, size.x() - position.x(), size.y() - position.y(), 0, 0, 1);
}

void Graphics::setup3D(const Viewer& viewer) noexcept {
	m_driver.setup3D(viewer);
	m_projection =
		Mat4r::perspective(
			deg2rad(viewer.fov()),
			real_t(viewer.viewportSize().x()) / viewer.viewportSize().y(),
			viewer.rangeMin(),
			viewer.rangeMax())
		* viewer.getViewMatrix();
}

void Graphics::cls(color_t color) const noexcept {
	m_driver.cls(color);
}

void Graphics::drawRect(
	const Vec2r& position,
	const Vec2r& size,
	color_t color) const noexcept {
	const auto transform = Mat4r::transform(
		{position.x() + size.x() / 2, position.y() + size.y() / 2, 0},
		{},
		{size.x(), size.y(), 1});
	m_rect.bind();
	prepareShader(transform, {}, color, false);
	m_rect.draw();
}

void Graphics::drawTexture(
	const Texture* tex,
	const Vec2r& position,
	const Vec2r& size,
	real_t angle,
	color_t color,
	const Mat4r& textureMatrix) const noexcept {
	if (tex) {
		const auto realSize = Vec2r {
			(size.x() != 0) ? size.x() : tex->size().x(),
			(size.y() != 0) ? size.y() : tex->size().y()};
		const auto transform = Mat4r::transform(
			{position + realSize / 2, 0},
			Quatr::fromAxis(deg2rad(angle), Vec3r{0, 0, 1}),
			{realSize, 1});
		tex->bind();
		m_rect.bind();
		prepareShader(transform, textureMatrix, color, true);
		m_rect.draw();
	}
}

void Graphics::drawText(
	const Font* font,
	const std::string& text,
	const Vec2r& position,
	color_t color) const noexcept {
	if (font) {
		auto fixedPos = Vec2r {position.x(), position.y() + font->m_maxHeight};
		for (auto i = size_t {0}; i < text.size(); ++i) {
			const auto quad = font->fontQuad(text[i], fixedPos);
			const auto texMatrix = Mat4r::transform(
				{quad.m_tex.x(), quad.m_tex.y(), 0},
				{},
				{quad.m_texSize.x(), quad.m_texSize.y(), 1}
			);
			drawTexture(
				font->m_tex.get(),
				quad.m_position,
				quad.m_size,
				0,
				color,
				texMatrix);
		}
	}
}

void Graphics::drawQuad(const Mat4r& transform, color_t color) const noexcept {
	m_quad.bind();
	prepareShader(transform, Mat4r{}, color, false);
	m_quad.draw();
}

void Graphics::drawLevel2D(
	const Level& level,
	const Vec2r& position,
	real_t size,
	color_t color) const noexcept {
	level.draw2D(*this, position, size, color);
}

void Graphics::drawLevel3D(const Level& level, real_t size, color_t color) const noexcept {
	level.draw3D(*this, size, color);
}

void Graphics::prepareShader(
	const Mat4r& transform,
	const Mat4r& textureMatrix,
	color_t color,
	bool useTexture) const noexcept {
	m_shader.prepare();
	m_shader.setInt(m_useTextureLoc, useTexture);
	m_shader.setInt(m_textureLoc, 0);
	m_shader.setMat4(m_mvpLoc, m_projection * transform);
	m_shader.setMat4(m_textureMatrixLoc, textureMatrix);
	m_shader.setVec4(
		m_baseColorLoc,
		{
			Color::redf(color),
			Color::greenf(color),
			Color::bluef(color),
			Color::alphaf(color)
		});
}
