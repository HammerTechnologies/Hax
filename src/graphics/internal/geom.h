#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include "vertex.h"

struct Geom {
	Geom(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) noexcept;
	~Geom() noexcept;
	void bind() const noexcept;
	void draw() const noexcept;
private:
	static constexpr size_t VERTEX_BUFFER = 0;
	static constexpr size_t INDEX_BUFFER = 1;

	std::array<uint32_t, 2> m_buffers;
	size_t m_numIndices;
};
