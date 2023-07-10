#include "geom.h"

namespace ngn {

Geom::Geom(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices, const prv::GraphicsDriver& driver) noexcept
: m_driver {driver},
	m_vertexBuffer {driver.createVertexBuffer(vertices)},
	m_indexBuffer {driver.createIndexBuffer(indices)},
	m_numIndices {indices.size()} {
}

void Geom::bind() const noexcept {
	m_driver.bindBuffers(*m_vertexBuffer, *m_indexBuffer);
}

void Geom::draw() const noexcept {
	m_driver.drawBuffers(m_numIndices);
}

} // namespace ngn
