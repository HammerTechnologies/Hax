#include "geom.h"

Geom::Geom(const GraphicsDriver& driver, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) noexcept
: m_driver{driver},
	m_vertexBuffer{driver.createVertexBuffer(vertices)},
	m_indexBuffer{driver.createIndexBuffer(indices)},
	m_numIndices{indices.size()} {
}

Geom::~Geom() {
	m_driver.deleteBuffer(m_vertexBuffer);
	m_driver.deleteBuffer(m_indexBuffer);
}

void Geom::bind() const noexcept {
	m_driver.bindBuffers(m_vertexBuffer, m_indexBuffer);
}

void Geom::draw() const noexcept {
	m_driver.drawBuffers(m_numIndices);
}
