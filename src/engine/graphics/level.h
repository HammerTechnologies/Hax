#pragma once

#include <memory>
#include "../math/mat4.h"
#include "../maze/generator.h"

struct Graph;
struct Graphics;

struct Level {
	Level(uint8_t width, uint8_t height, uint32_t seed) noexcept
	: m_maze{generateMaze(width, height, seed)} {}
private:
	std::unique_ptr<Graph> m_maze;

	void draw2D(
		const Graphics& graphics,
		real_t x,
		real_t y,
		real_t size,
		uint32_t color) const noexcept;
	static void drawNode2D(
		const Graphics& graphics,
		const std::shared_ptr<GraphNode>& gn,
		real_t x,
		real_t y,
		real_t size,
		uint32_t color) noexcept;

	void draw3D(const Graphics& graphics, real_t size, uint32_t color) const noexcept;
	static void drawNode3D(
		const Graphics& graphics,
		const std::shared_ptr<GraphNode>& gn,
		uint16_t tileX,
		uint16_t tileY,
		real_t size,
		uint32_t color) noexcept;
	static void drawWWall(
		const Graphics& graphics,
		uint16_t tileX,
		uint16_t tileY,
		real_t size,
		uint32_t color) noexcept;
	static void drawEWall(
		const Graphics& graphics,
		uint16_t tileX,
		uint16_t tileY,
		real_t size,
		uint32_t color) noexcept;
	static void drawNWall(
		const Graphics& graphics,
		uint16_t tileX,
		uint16_t tileY,
		real_t size,
		uint32_t color) noexcept;
	static void drawSWall(
		const Graphics& graphics,
		uint16_t tileX,
		uint16_t tileY,
		real_t size,
		uint32_t color) noexcept;
	static void drawWEWall(
		const Graphics& graphics,
		uint16_t tileX,
		uint16_t tileY,
		real_t size,
		uint32_t color) noexcept;
	static void drawNSWall(
		const Graphics& graphics,
		uint16_t tileX,
		uint16_t tileY,
		real_t size,
		uint32_t color) noexcept;
	static void drawXWall(
		const Graphics& graphics,
		real_t x,
		real_t z,
		real_t width,
		real_t height,
		uint32_t color) noexcept;
	static void drawZWall(
		const Graphics& graphics,
		real_t x,
		real_t z,
		real_t width,
		real_t height,
		uint32_t color) noexcept;

	friend struct Graphics;
};
