#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include "graphnode.h"

/**
 * Grafo de nodos.
 */
struct Graph {
	Graph(uint8_t m_width, uint8_t m_height);

	uint8_t getWidth() noexcept;
	uint8_t getHeight() noexcept;
	bool isEmptyAt(uint8_t x, uint8_t y) noexcept;
	bool isEmptyAdjacentTo(std::shared_ptr<GraphNode> &node, Direction direction) noexcept;
	std::shared_ptr<GraphNode> getNodeAt(uint8_t x, uint8_t y) noexcept;
	std::shared_ptr<GraphNode> getNodeAdjacentTo(std::shared_ptr<GraphNode> node, Direction direction) noexcept;
	bool isAvailable(std::shared_ptr<GraphNode> &node, Direction direction) noexcept;
	bool isWestAvailable(std::shared_ptr<GraphNode> &node) noexcept;
	bool isEastAvailable(std::shared_ptr<GraphNode> &node) noexcept;
	bool isNorthAvailable(std::shared_ptr<GraphNode> &node) noexcept;
	bool isSouthAvailable(std::shared_ptr<GraphNode> &node) noexcept;

private:
	uint8_t m_width;
	uint8_t m_height;
	std::vector<std::shared_ptr<GraphNode>> m_nodes;
};

#ifndef EMSCRIPTEN
std::ostream &operator<<(std::ostream &os, std::unique_ptr<Graph> &g);
#endif
