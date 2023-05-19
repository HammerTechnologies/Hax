#include <glad/glad.h>
#include "shader.h"
#include "vertex.h"

Shader::Shader(const std::string& vertex, const std::string& fragment) noexcept
: m_id(0) {
#ifdef EMSCRIPTEN
	const std::string vertexCode = vertex;
	const std::string fragmentCode = "precision mediump float;\n" + fragment;
#else
	const std::string vertexCode = vertex;
	const std::string fragmentCode = fragment;
#endif
	char errorOutput[1024];
	GLint retCode = 0;

	// Create vertex shader
	const char* cvertex = vertexCode.c_str();
	const GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &cvertex, NULL);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(vshader, sizeof(errorOutput), NULL, errorOutput);
		m_error = errorOutput;
		glDeleteShader(vshader);
		return;
	}

	// Create fragment shader
	const char* cfragment = fragmentCode.c_str();
	const GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &cfragment, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetShaderInfoLog(fshader, sizeof(errorOutput), NULL, errorOutput);
		m_error = errorOutput;
		glDeleteShader(vshader);
		glDeleteShader(fshader);
		return;
	}

	// Create program
	const size_t id = glCreateProgram();
	glAttachShader(id, vshader);
	glAttachShader(id, fshader);
	glLinkProgram(id);
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	glGetProgramiv(id, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetProgramInfoLog(id, sizeof(errorOutput), NULL, errorOutput);
		m_error = errorOutput;
		glDeleteProgram(id);
		return;
	}
	m_id = id;
	m_vertexPos = glGetAttribLocation(m_id, "vertexPos");
	m_vertexColor = glGetAttribLocation(m_id, "vertexColor");
	m_vertexTexCoords = glGetAttribLocation(m_id, "vertexTexCoords");
}

Shader::~Shader() noexcept {
	glDeleteProgram(m_id);
}

int32_t Shader::getUniform(const std::string& name) const noexcept {
	return glGetUniformLocation(m_id, name.c_str());
}

void Shader::prepare() const noexcept {
	glUseProgram(m_id);
	setAttrib(m_vertexPos, 3, false, offsetof(Vertex, m_position));
	setAttrib(m_vertexColor, 4, true, offsetof(Vertex, m_color));
	setAttrib(m_vertexTexCoords, 2, false, offsetof(Vertex, m_texCoords));
}

void Shader::setInt(int32_t location, int32_t value) const noexcept {
	glUniform1i(location, value);
}

void Shader::setReal(int32_t location, real_t value) const noexcept {
	glUniform1f(location, value);
}

void Shader::setVec2(int32_t location, real_t x, real_t y) const noexcept {
	glUniform2f(location, x, y);
}

void Shader::setVec3(int32_t location, const Vec3r& v) const noexcept {
	glUniform3f(location, v.m_x, v.m_y, v.m_z);
}

void Shader::setVec4(int32_t location, real_t x, real_t y, real_t z, real_t w) const noexcept {
	glUniform4f(location, x, y, z, w);
}

void Shader::setMat4(int32_t location, const Mat4r& m) const noexcept {
	glUniformMatrix4fv(location, 1, false, m.m_data.data());
}

void Shader::setAttrib(int32_t location, size_t size, bool normalize, size_t offset) const noexcept {
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
