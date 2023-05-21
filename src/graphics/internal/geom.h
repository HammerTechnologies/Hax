#pragma once

#include <cstdint>
#include <vector>
#include "vertex.h"

struct Geom {
	Geom(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) noexcept;
	~Geom() noexcept;
	void bind() const noexcept;
	void draw() const noexcept;
private:
	uint32_t m_vertexBuffer;
	uint32_t m_indexBuffer;
	size_t m_numIndices;
};
