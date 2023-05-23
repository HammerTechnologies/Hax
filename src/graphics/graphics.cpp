#include <string>
#include <glad/glad.h>
#include "font.h"
#include "graphics.h"
#include "texture.h"

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

Graphics::Graphics(void*(* loader)(const char*)) noexcept
: m_init{gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(loader)) != 0},
	m_shader(VERTEX_SHADER, FRAGMENT_SHADER),
	m_rect(
		{
			Vertex(Vec3r(static_cast<real_t>(-0.5), static_cast<real_t>(-0.5), 0), Color::WHITE, 0, 0),
			Vertex(Vec3r(static_cast<real_t>( 0.5), static_cast<real_t>(-0.5), 0), Color::WHITE, 1, 0),
			Vertex(Vec3r(static_cast<real_t>( 0.5), static_cast<real_t>( 0.5), 0), Color::WHITE, 1, 1),
			Vertex(Vec3r(static_cast<real_t>(-0.5), static_cast<real_t>( 0.5), 0), Color::WHITE, 0, 1)},
		{0, 1, 2, 3}),
	m_mvpLoc{m_shader.getUniform("mvp")},
	m_textureMatrixLoc{m_shader.getUniform("textureMatrix")},
	m_baseColorLoc{m_shader.getUniform("baseColor")},
	m_useTextureLoc{m_shader.getUniform("useTexture")},
	m_textureLoc{m_shader.getUniform("texture")},
	m_projection{} {}

void Graphics::setup2D(uint16_t x, uint16_t y, uint16_t w, uint16_t h) noexcept {
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CW);
	glViewport(x, y, w, h);
	glScissor(x, y, w, h);
	m_projection = Mat4r::ortho(0, w - x, h - y, 0, 0, 1);
}

void Graphics::cls(uint32_t color) const noexcept {
	glClearColor(Color::redf(color), Color::greenf(color), Color::bluef(color), Color::alphaf(color));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::drawRect(
	real_t x,
	real_t y,
	real_t width,
	real_t height,
	uint32_t color) const noexcept {
	const Mat4r transform = Mat4r::transform(
		Vec3r{x + width / 2, y + height / 2, 0},
		Quatr{},
		Vec3r{width, height, 1});
	m_rect.bind();
	prepareShader(transform, Mat4r{}, color, false);
	m_rect.draw();
}

void Graphics::drawTexture(
	const Texture& tex,
	real_t x,
	real_t y,
	real_t width,
	real_t height,
	real_t angle,
	uint32_t color,
	const Mat4r& textureMatrix) const noexcept {
	if (tex.isValid()) {
		const real_t realWidth = (width != 0) ? width : tex.getWidth();
		const real_t realHeight = (height != 0) ? height : tex.getHeight();
		const Mat4r transform = Mat4r::transform(
			Vec3r{x + realWidth / 2, y + realHeight / 2, 0},
			Quatr::fromAxis(deg2rad(angle), Vec3r{0, 0, 1}),
			Vec3r{realWidth, realHeight, 1});
		tex.bind();
		m_rect.bind();
		prepareShader(transform, textureMatrix, color, true);
		m_rect.draw();
	}
}

void Graphics::drawText(
	const Font& font,
	const std::string& text,
	real_t x,
	real_t y,
	uint32_t color) const noexcept {
	if (font.isValid()) {
		y += font.m_maxHeight;
		for (size_t i = 0; i < text.size(); ++i) {
			const FontQuad quad = font.getFontQuad(text[i], x, y);
			const Mat4r texMatrix = Mat4r::transform(
				Vec3r{quad.m_u, quad.m_v, 0},
				Quatr{},
				Vec3r{quad.m_us, quad.m_vs, 1}
			);
			drawTexture(*font.m_tex, quad.m_x, quad.m_y, quad.m_width, quad.m_height, 0, color, texMatrix);
		}
	}
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
