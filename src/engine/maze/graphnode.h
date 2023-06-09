#pragma once

#include <iostream>
#include <cstdint>
#include <memory>
#include <array>
#include <memory>
#include "direction.h"


/**
 * Nodo del grafo.
 */
struct GraphNode {
	GraphNode() noexcept;
	GraphNode(uint8_t x, uint8_t y) noexcept;
	uint8_t getX() noexcept;
	uint8_t getY() noexcept;
	uint8_t getVisited() noexcept;
	void visit() noexcept;
	bool isConnected(Direction direction) noexcept;
	bool isDisconnected(Direction edge) noexcept;
	bool isDisconnected() noexcept;
	bool hasEast() noexcept;
	bool hasWest() noexcept;
	bool hasNorth() noexcept;
	bool hasSouth() noexcept;
	void set(uint8_t nx, uint8_t ny) noexcept;
	void connect(std::shared_ptr<GraphNode> &node, Direction direction) noexcept;

private:
	uint8_t m_x = 0;
	uint8_t m_y = 0;
	uint8_t m_visited = 0;
	std::array<std::weak_ptr<GraphNode>, DIRECTIONS> m_edges;
};

#ifndef EMSCRIPTEN
std::ostream &operator<<(std::ostream &os, std::shared_ptr<GraphNode> &gn);
#endif
