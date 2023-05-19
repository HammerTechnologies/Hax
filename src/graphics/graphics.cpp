#include <string>
#include <glad/glad.h>
#include "graphics.h"

constexpr const char* VERTEX_SHADER = R"VS(
uniform mat4 mvp;

attribute vec3 vertexPos;
attribute vec4 vertexColor;
attribute vec2 vertexTexCoords;

varying vec4 fragColor;
varying vec2 fragTexCoords;

void main() {
	gl_Position = mvp * vec4(vertexPos, 1);
	fragColor = vertexColor;
	fragTexCoords = vertexTexCoords;
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

Graphics::Graphics() noexcept
: m_shader(VERTEX_SHADER, FRAGMENT_SHADER),
	m_rect(
		{
			Vertex(Vec3r(static_cast<real_t>(-0.5), static_cast<real_t>( 0.5), 0), Color::WHITE, 0, 0),
			Vertex(Vec3r(static_cast<real_t>( 0.5), static_cast<real_t>( 0.5), 0), Color::WHITE, 1, 0),
			Vertex(Vec3r(static_cast<real_t>( 0.5), static_cast<real_t>(-0.5), 0), Color::WHITE, 1, 1),
			Vertex(Vec3r(static_cast<real_t>(-0.5), static_cast<real_t>(-0.5), 0), Color::WHITE, 0, 1)},
		{0, 1, 2, 3}),
	m_mvpLoc{m_shader.getUniform("mvp")},
	m_baseColorLoc{m_shader.getUniform("baseColor")},
	m_useTextureLoc{m_shader.getUniform("useTexture")},
	m_textureLoc{m_shader.getUniform("texture")},
	m_projection{} {}

void Graphics::setup2D(uint16_t x, uint16_t y, uint16_t w, uint16_t h) noexcept {
	glEnable(GL_SCISSOR_TEST);
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

void Graphics::drawRect(real_t x, real_t y, real_t width, real_t height, uint32_t color) const noexcept {
	const Mat4r transform = Mat4r::transform(
		Vec3r{x + width / 2, y + height / 2, 0},
		Quatr{},
		Vec3r{width, height, 1});
	m_rect.bind();
	prepareShader(transform, color);
	m_rect.draw();
	m_rect.unbind();
}

void Graphics::prepareShader(const Mat4r& transform, uint32_t color) const noexcept {
	m_shader.prepare();
	m_shader.setMat4(m_mvpLoc, m_projection * transform);
	m_shader.setVec4(
		m_baseColorLoc,
		Color::redf(color),
		Color::greenf(color),
		Color::bluef(color),
		Color::alphaf(color));
}
