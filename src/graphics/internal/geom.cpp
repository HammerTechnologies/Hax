#include <glad/glad.h>
#include "geom.h"

Geom::Geom(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) noexcept {
	glGenBuffers(m_buffers.size(), m_buffers.data());
	m_numIndices = indices.size();
	bind();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);
}

Geom::~Geom() {
	glDeleteBuffers(m_buffers.size(), m_buffers.data());
}

void Geom::bind() const noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[VERTEX_BUFFER]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDEX_BUFFER]);
}

void Geom::draw() const noexcept {
	glDrawElements(GL_TRIANGLE_FAN, m_numIndices, GL_UNSIGNED_SHORT, 0);
}
