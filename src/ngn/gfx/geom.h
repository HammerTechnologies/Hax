#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "../_prv/graphics_driver.h"
#include "vertex.h"

namespace ngn {

struct Geom {
private:
	const prv::GraphicsDriver& m_driver;
	std::unique_ptr<prv::VertexBuffer> m_vertexBuffer;
	std::unique_ptr<prv::IndexBuffer> m_indexBuffer;
	size_t m_numIndices;

	Geom(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices, const prv::GraphicsDriver& driver) noexcept;
	void bind() const noexcept;
	void draw() const noexcept;

	friend struct Graphics;
};

} // namespace ngn
