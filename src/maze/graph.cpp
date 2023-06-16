#include "graph.h"

Graph::Graph(uint8_t width, uint8_t height)
	: m_width(width), m_height(height)
{
	// Reservamos la memoria de los nodos.
	m_nodes.resize(width * height);
	for (uint8_t y = 0; y < height; y++) {
		for (uint8_t x = 0; x < width; x++) {
			uint16_t index = y * width + x;
			m_nodes[index] = std::make_shared<GraphNode>(x, y);
		}
	}
}

uint8_t Graph::getWidth() noexcept {
	return m_width;
}

uint8_t Graph::getHeight() noexcept {
	return m_height;
}

bool Graph::isEmptyAt(uint8_t x, uint8_t y) noexcept {
	std::shared_ptr<GraphNode> node = getNodeAt(x, y);
	if (node == nullptr)
		return false;

	return node->isDisconnected();
}

bool Graph::isEmptyAdjacentTo(std::shared_ptr<GraphNode> &node, Direction direction) noexcept {
	std::shared_ptr<GraphNode> adjacent = getNodeAdjacentTo(node, direction);
	if (adjacent == nullptr)
		return false;

	return adjacent->isDisconnected();
}

std::shared_ptr<GraphNode> Graph::getNodeAt(uint8_t x, uint8_t y) noexcept {
	if (x >= m_width || y >= m_height)
		return nullptr;

	uint16_t index = y * m_width + x;
	return m_nodes[index];
}

std::shared_ptr<GraphNode> Graph::getNodeAdjacentTo(std::shared_ptr<GraphNode> node, Direction direction) noexcept {
	if (direction == Direction::East)
		return getNodeAt(node->getX() + 1, node->getY());
	else if (direction == Direction::West)
		return getNodeAt(node->getX() - 1, node->getY());
	else if (direction == Direction::South)
		return getNodeAt(node->getX(), node->getY() + 1);
	else if (direction == Direction::North)
		return getNodeAt(node->getX(), node->getY() - 1);
	return nullptr;
}

bool Graph::isAvailable(std::shared_ptr<GraphNode> &node, Direction direction) noexcept {
	return node->isDisconnected(direction) && isEmptyAdjacentTo(node, direction);
}

bool Graph::isWestAvailable(std::shared_ptr<GraphNode> &node) noexcept {
	return node->getX() > 0 && isAvailable(node, Direction::West);
}

bool Graph::isEastAvailable(std::shared_ptr<GraphNode> &node) noexcept {
	return node->getX() < m_width - 1 && isAvailable(node, Direction::East);
}

bool Graph::isNorthAvailable(std::shared_ptr<GraphNode> &node) noexcept {
	return node->getY() > 0 && isAvailable(node, Direction::North);
}

bool Graph::isSouthAvailable(std::shared_ptr<GraphNode> &node) noexcept {
	return node->getY() < m_height - 1 && isAvailable(node, Direction::South);
}

#ifndef EMSCRIPTEN
/**
 * Sobrecarga del operador << para poder imprimir un grafo
 */
std::ostream &operator<<(std::ostream &os, std::unique_ptr<Graph> &g) {
	for (uint8_t y = 0; y < g->getHeight(); y++)
	{
		for (uint8_t x = 0; x < g->getWidth(); x++)
		{
			std::shared_ptr<GraphNode> node = g->getNodeAt(x, y);
			if (node->getVisited() == 0)
				os << "\x1B[0;32m";
			else
				os << "\x1B[0;33m";

			os << node;
			os << "\x1B[0m";
		}
		os << std::endl;
	}
	return os;
}
#endif
