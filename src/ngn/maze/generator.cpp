#include <stack>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <random>
#include <memory>

#include "generator.h"
#include "graph.h"
#include "graphnode.h"

const std::unique_ptr<Graph> generateMaze(uint8_t width, uint8_t height, uint32_t seed) noexcept {
	std::unique_ptr<Graph> graph = std::make_unique<Graph>(width, height);

	std::vector<Direction> availableDirections;
	std::stack<std::shared_ptr<GraphNode>> stack;

	std::srand(seed);

	std::shared_ptr<GraphNode> currentNode = graph->getNodeAt(0, 0);
	stack.push(currentNode);

	while (stack.size() > 0) {
		// Limpiamos la lista de direcciones y añadimos solo
		// aquellas direcciones que están disponibles.
		availableDirections.clear();
		if (graph->isWestAvailable(currentNode))
			availableDirections.push_back(Direction::West);

		if (graph->isEastAvailable(currentNode))
			availableDirections.push_back(Direction::East);

		if (graph->isNorthAvailable(currentNode))
			availableDirections.push_back(Direction::North);

		if (graph->isSouthAvailable(currentNode))
			availableDirections.push_back(Direction::South);

		// Si no hay direcciones disponibles, entonces
		// retrocedemos en el stack.
		if (availableDirections.size() == 0) {
			currentNode = stack.top();
			currentNode->visit();
			stack.pop();
			continue;
		}

		// Obtenemos el siguiente nodo a partir de una dirección aleatoria.
		uint8_t nextDirectionIndex = std::rand() % availableDirections.size();
		Direction nextDirection = availableDirections[nextDirectionIndex];
		std::shared_ptr<GraphNode> nextNode = graph->getNodeAdjacentTo(currentNode, nextDirection);
		if (nextNode == nullptr) {
			// TODO: Deberíamos petar MUY FUERTE
		}

		// Conectamos los dos nodos entre sí.
		currentNode->connect(nextNode, nextDirection);
		nextNode->connect(currentNode, getDirectionOpposite(nextDirection));

		// Movemos el currentNode al nextNode y lo añadimos
		// al stack.
		currentNode = nextNode;
		stack.push(currentNode);
	}
	return graph;
}
