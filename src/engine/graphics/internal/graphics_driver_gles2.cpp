#include <array>
#include <glad/glad.h>
#include "../../logger.h"
#include "../viewer.h"
#include "graphics_driver.h"
#include "vertex.h"

GraphicsDriver::GraphicsDriver(ContextDriver::GlGetProcAddress loader, const Logger& logger) noexcept
: m_logger(logger),
	m_init{gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(loader)) != 0} {
	if (!m_init) {
		m_logger.error("Could not initialize GL");
	}
}

void GraphicsDriver::setup2D(uint16_t x, uint16_t y, uint16_t w, uint16_t h) const noexcept {
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(x, y, w, h);
	glScissor(x, y, w, h);
}

void GraphicsDriver::setup3D(const Viewer& viewer) const noexcept {
	glDisable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CW);
	glViewport(
		viewer.m_viewportX,
		viewer.m_viewportY,
		viewer.m_viewportWidth,
		viewer.m_viewportHeight);
	glScissor(
		viewer.m_viewportX,
		viewer.m_viewportY,
		viewer.m_viewportWidth,
		viewer.m_viewportHeight);
}

void GraphicsDriver::cls(uint32_t color = Color::BLACK) const noexcept {
	glClearColor(Color::redf(color), Color::greenf(color), Color::bluef(color), Color::alphaf(color));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

VertexBuffer GraphicsDriver::createVertexBuffer(const std::vector<Vertex>& vertices) const noexcept {
	auto buffer = 0U;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	return {buffer};
}

IndexBuffer GraphicsDriver::createIndexBuffer(const std::vector<uint16_t>& indices) const noexcept {
	auto buffer = 0U;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);
	return {buffer};
}

void GraphicsDriver::bindBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer) const noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.m_id);
}

void GraphicsDriver::drawBuffers(size_t numIndices) const noexcept {
	glDrawElements(GL_TRIANGLE_FAN, numIndices, GL_UNSIGNED_SHORT, 0);
}

void GraphicsDriver::deleteBuffer(const VertexBuffer& buffer) const noexcept {
	glDeleteBuffers(1, &buffer.m_id);
}

void GraphicsDriver::deleteBuffer(const IndexBuffer& buffer) const noexcept {
	glDeleteBuffers(1, &buffer.m_id);
}

GpuProgram GraphicsDriver::createProgram(const std::string& vertex, const std::string& fragment) const noexcept {
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
		return {0};
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
		return {0};
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
		return {0};
	}

	return {id};
}

void GraphicsDriver::deleteProgram(const GpuProgram& program) const noexcept {
	glDeleteProgram(program.m_id);
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

void GraphicsDriver::setProgramUniform(int32_t location, real_t x, real_t y) const noexcept {
	glUniform2f(location, x, y);
}

void GraphicsDriver::setProgramUniform(int32_t location, const Vec3r& v) const noexcept {
	glUniform3fv(location, 1, v.data());
}

void GraphicsDriver::setProgramUniform(int32_t location, real_t x, real_t y, real_t z, real_t w) const noexcept {
	glUniform4f(location, x, y, z, w);
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

DriverTexture GraphicsDriver::createTexture() const noexcept {
	auto id = 0U;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return {id};
}

void GraphicsDriver::deleteTexture(const DriverTexture& texture) const noexcept {
	glDeleteTextures(1, &texture.m_id);
}

void GraphicsDriver::bindTexture(const DriverTexture& texture) const noexcept {
	glBindTexture(GL_TEXTURE_2D, texture.m_id);
}

void GraphicsDriver::setTexturePixels(
	const DriverTexture& texture,
	uint16_t width,
	uint16_t height,
	const uint32_t* pixels) const noexcept {
	bindTexture(texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pixels);
}
