#pragma once

#include <cstdint>
#include <stack>
#include <vector>
#include <memory>
#include "graph.h"
#include "graphnode.h"

const std::unique_ptr<Graph> generateMaze(uint8_t width, uint8_t height, uint32_t seed) noexcept;
