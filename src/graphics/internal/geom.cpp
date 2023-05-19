#include <glad/glad.h>
#include "geom.h"

Geom::Geom(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) noexcept {
	GLuint buffers[2];
	glGenBuffers(2, buffers);
	m_vertexBuffer = buffers[0];
	m_indexBuffer = buffers[1];
	m_numIndices = indices.size();
	bind();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);
	unbind();
}

Geom::~Geom() {
	GLuint buffers[] = {m_vertexBuffer, m_indexBuffer};
	glDeleteBuffers(2, buffers);
}

void Geom::bind() const noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
}

void Geom::unbind() const noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Geom::draw() const noexcept {
	glDrawElements(GL_TRIANGLE_FAN, m_numIndices, GL_UNSIGNED_SHORT, 0);
}
