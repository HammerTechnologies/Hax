#include <array>
#include <glad/glad.h>
#include "../gfx/viewer.h"
#include "../logger.h"
#include "graphics_driver.h"
#include "vertex.h"

namespace ngn::prv {

GraphicsDriver::GraphicsDriver(ContextDriver::GlGetProcAddress loader, const Logger& logger) noexcept
: m_logger(logger),
	m_init{gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(loader)) != 0} {
	if (!m_init) {
		m_logger.error("Could not initialize GL");
	}
}

void GraphicsDriver::setup2D(const Vec2<uint16_t>& position, const Vec2<uint16_t> size) const noexcept {
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glScissor(position.x(), position.y(), size.x(), size.y());
	glViewport(position.x(), position.y(), size.x(), size.y());
}

void GraphicsDriver::setup3D(const Viewer& viewer) const noexcept {
	glDisable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CW);
	glScissor(
		viewer.viewportPosition().x(),
		viewer.viewportPosition().y(),
		viewer.viewportSize().x(),
		viewer.viewportSize().y());
	glViewport(
		viewer.viewportPosition().x(),
		viewer.viewportPosition().y(),
		viewer.viewportSize().x(),
		viewer.viewportSize().y());
}

void GraphicsDriver::cls(color_t color = Color::BLACK) const noexcept {
	glClearColor(Color::redf(color), Color::greenf(color), Color::bluef(color), Color::alphaf(color));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

std::unique_ptr<VertexBuffer> GraphicsDriver::createVertexBuffer(const std::vector<Vertex>& vertices) const noexcept {
	auto buffer = GLuint {0};
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	return std::make_unique<VertexBuffer>(buffer);
}

std::unique_ptr<IndexBuffer> GraphicsDriver::createIndexBuffer(const std::vector<uint16_t>& indices) const noexcept {
	auto buffer = GLuint {0};
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);
	return std::make_unique<IndexBuffer>(buffer);
}

void GraphicsDriver::bindBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer) const noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.m_id);
}

void GraphicsDriver::drawBuffers(size_t numIndices) const noexcept {
	glDrawElements(GL_TRIANGLE_FAN, numIndices, GL_UNSIGNED_SHORT, 0);
}

std::unique_ptr<GpuProgram> GraphicsDriver::createProgram(const std::string& vertex, const std::string& fragment) const noexcept {
#ifdef EMSCRIPTEN
	const auto vertexCode = vertex;
	const auto fragmentCode = "precision mediump float;\n" + fragment;
#else
	const auto vertexCode = vertex;
	const auto fragmentCode = fragment;
#endif

	auto errorOutput = std::array<char, 1024> {};
	auto retCode = 0;

	// Create vertex shader
	const auto cvertex = vertexCode.c_str();
	const auto vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &cvertex, nullptr);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(vshader, errorOutput.size(), nullptr, errorOutput.data());
		m_logger.error(errorOutput.data());
		glDeleteShader(vshader);
		return nullptr;
	}

	// Create fragment shader
	const auto cfragment = fragmentCode.c_str();
	const auto fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &cfragment, nullptr);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(fshader, errorOutput.size(), nullptr, errorOutput.data());
		m_logger.error(errorOutput.data());
		glDeleteShader(vshader);
		glDeleteShader(fshader);
		return nullptr;
	}

	// Create program
	const auto id = glCreateProgram();
	glAttachShader(id, vshader);
	glAttachShader(id, fshader);
	glLinkProgram(id);
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	glGetProgramiv(id, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetProgramInfoLog(id, errorOutput.size(), nullptr, errorOutput.data());
		m_logger.error(errorOutput.data());
		glDeleteProgram(id);
		return nullptr;
	}

	return std::make_unique<GpuProgram>(id);
}

void GraphicsDriver::useProgram(const GpuProgram& program) const noexcept {
	glUseProgram(program.m_id);
}

int32_t GraphicsDriver::getProgramUniformLocation(const GpuProgram& program, const std::string& name) const noexcept {
	return glGetUniformLocation(program.m_id, name.c_str());
}

void GraphicsDriver::setProgramUniform(int32_t location, int32_t value) const noexcept {
	glUniform1i(location, value);
}

void GraphicsDriver::setProgramUniform(int32_t location, real_t value) const noexcept {
	glUniform1f(location, value);
}

void GraphicsDriver::setProgramUniform(int32_t location, const Vec2r& v) const noexcept {
	glUniform2fv(location, 1, v.data());
}

void GraphicsDriver::setProgramUniform(int32_t location, const Vec3r& v) const noexcept {
	glUniform3fv(location, 1, v.data());
}

void GraphicsDriver::setProgramUniform(int32_t location, const Vec4r& v) const noexcept {
	glUniform4fv(location, 1, v.data());
}

void GraphicsDriver::setProgramUniform(int32_t location, const Mat4r& m) const noexcept {
	glUniformMatrix4fv(location, 1, false, m.data());
}

int32_t GraphicsDriver::getProgramAttribLocation(const GpuProgram& program, const std::string& name) const noexcept {
	return glGetAttribLocation(program.m_id, name.c_str());
}

void GraphicsDriver::setProgramAttrib(int32_t location, size_t size, bool normalize, size_t offset) const noexcept {
	if (location != -1) {
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(
			location,
			size,
			normalize ? GL_UNSIGNED_BYTE : GL_FLOAT,
			normalize,
			sizeof(Vertex),
			reinterpret_cast<const void*>(offset)
		);
	}
}

std::unique_ptr<DriverTexture> GraphicsDriver::createTexture() const noexcept {
	auto id = GLuint {0};
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return std::make_unique<DriverTexture>(id);
}

void GraphicsDriver::bindTexture(const DriverTexture& texture) const noexcept {
	glBindTexture(GL_TEXTURE_2D, texture.m_id);
}

void GraphicsDriver::setTexturePixels(
	const DriverTexture& texture,
	const Vec2<uint16_t>& size,
	non_owning_ptr<const color_t> pixels) const noexcept {
	bindTexture(texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		size.x(),
		size.y(),
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pixels);
}

void VertexBufferDeleter(uint32_t vb) {
	glDeleteBuffers(1, &vb);
}

void IndexBufferDeleter(uint32_t ib) {
	glDeleteBuffers(1, &ib);
}

void GpuProgramDeleter(uint32_t p) {
	glDeleteProgram(p);
}

void DriverTextureDeleter(uint32_t t) {
	glDeleteTextures(1, &t);
}

} // namespace ngn::prv
