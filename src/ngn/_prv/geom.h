#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "graphics_driver.h"
#include "vertex.h"

namespace ngn::prv {

struct Geom {
	Geom(const GraphicsDriver& driver, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) noexcept;

	void bind() const noexcept;
	void draw() const noexcept;
private:
	const GraphicsDriver& m_driver;
	std::unique_ptr<VertexBuffer> m_vertexBuffer;
	std::unique_ptr<IndexBuffer> m_indexBuffer;
	size_t m_numIndices;
};

} // namespace ngn::prv
