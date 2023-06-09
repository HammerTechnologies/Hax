#include <array>
#include <cstddef>
#include "shader.h"
#include "vertex.h"

Shader::Shader(const GraphicsDriver& driver, const std::string& vertex, const std::string& fragment) noexcept
: m_driver{driver},
	m_program{m_driver.createProgram(vertex, fragment)},
	m_vertexPos{m_driver.getProgramAttribLocation(m_program, "vertexPos")},
	m_vertexColor{m_driver.getProgramAttribLocation(m_program, "vertexColor")},
	m_vertexTexCoords{m_driver.getProgramAttribLocation(m_program, "vertexTexCoords")} {
}

Shader::~Shader() noexcept {
	m_driver.deleteProgram(m_program);
}

int32_t Shader::getUniform(const std::string& name) const noexcept {
	return m_driver.getProgramUniformLocation(m_program, name);
}

void Shader::prepare() const noexcept {
	m_driver.useProgram(m_program);
	m_driver.setProgramAttrib(m_vertexPos, 3, false, offsetof(Vertex, m_position));
	m_driver.setProgramAttrib(m_vertexColor, 4, true, offsetof(Vertex, m_color));
	m_driver.setProgramAttrib(m_vertexTexCoords, 2, false, offsetof(Vertex, m_texCoords));
}

void Shader::setInt(int32_t location, int32_t value) const noexcept {
	m_driver.setProgramUniform(location, value);
}

void Shader::setReal(int32_t location, real_t value) const noexcept {
	m_driver.setProgramUniform(location, value);
}

void Shader::setVec2(int32_t location, real_t x, real_t y) const noexcept {
	m_driver.setProgramUniform(location, x, y);
}

void Shader::setVec3(int32_t location, const Vec3r& v) const noexcept {
	m_driver.setProgramUniform(location, v);
}

void Shader::setVec4(int32_t location, real_t x, real_t y, real_t z, real_t w) const noexcept {
	m_driver.setProgramUniform(location, x, y, z, w);
}

void Shader::setMat4(int32_t location, const Mat4r& m) const noexcept {
	m_driver.setProgramUniform(location, m);
}
