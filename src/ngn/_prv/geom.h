#pragma once

#include <cstdint>
#include <vector>
#include "graphics_driver.h"
#include "vertex.h"

namespace ngn::prv {

struct Geom {
	Geom(const GraphicsDriver& driver, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) noexcept;
	~Geom() noexcept;
	void bind() const noexcept;
	void draw() const noexcept;
private:
	const GraphicsDriver& m_driver;
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
	size_t m_numIndices;
};

} // namespace ngn::prv
