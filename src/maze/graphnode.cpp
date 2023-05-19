#include "graphnode.h"

GraphNode::GraphNode(uint8_t x, uint8_t y) noexcept : m_x(x), m_y(y) {}

uint8_t GraphNode::getX() noexcept {
	return m_x;
}

uint8_t GraphNode::getY() noexcept {
	return m_y;
}

uint8_t GraphNode::getVisited() noexcept {
	return m_visited;
}

void GraphNode::visit() noexcept {
	m_visited++;
}

bool GraphNode::isConnected(Direction direction) noexcept {
	return m_edges[static_cast<uint8_t>(direction)].use_count() > 0;
}

bool GraphNode::isDisconnected(Direction direction) noexcept {
	return !isConnected(direction);
}

bool GraphNode::isDisconnected() noexcept {
	return !isConnected(Direction::West)
			&& !isConnected(Direction::East)
			&& !isConnected(Direction::North)
			&& !isConnected(Direction::South);
}

bool GraphNode::hasEast() noexcept {
	return !isDisconnected(Direction::East);
}

bool GraphNode::hasWest() noexcept {
	return !isDisconnected(Direction::West);
}

bool GraphNode::hasNorth() noexcept {
	return !isDisconnected(Direction::North);
}

bool GraphNode::hasSouth() noexcept {
	return !isDisconnected(Direction::South);
}

void GraphNode::set(uint8_t nx, uint8_t ny) noexcept {
	m_x = nx;
	m_y = ny;
}

void GraphNode::connect(std::shared_ptr<GraphNode> &node, Direction direction) noexcept {
	m_edges[static_cast<uint8_t>(direction)] = node;
}

#ifndef EMSCRIPTEN
/**
 * Sobrecarga del operador << para poder imprimir un nodo
 */
std::ostream &operator<<(std::ostream &os, std::shared_ptr<GraphNode> &gn) {
	if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		os << "╴";
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth())	{
		os << "╶";
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		os << "╵";
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		os << "╷";
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		os << " ";
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		os << "─";
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		os << "│";
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		os << "┌";
	} else if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		os << "┐";
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		os << "└";
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		os << "┘";
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		os << "├";
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		os << "┤";
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		os << "┬";
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		os << "┴";
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		os << "┼";
	}
	return os;
}
#endif
