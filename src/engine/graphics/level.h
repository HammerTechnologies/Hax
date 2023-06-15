#pragma once

#include <memory>
#include "../math/mat4.h"
#include "../math/vec2.h"
#include "../maze/generator.h"

struct Graph;
struct Graphics;

struct Level {
	Level(const Vec2<uint8_t>& size, uint32_t seed) noexcept
	: m_maze{generateMaze(size.x(), size.y(), seed)} {}

	Vec2<uint8_t> size() const noexcept { return {m_maze->getWidth(), m_maze->getHeight()}; }
private:
	std::unique_ptr<Graph> m_maze;

	void draw2D(
		const Graphics& graphics,
		const Vec2r& position,
		real_t size,
		color_t color) const noexcept;
	static void drawNode2D(
		const Graphics& graphics,
		const std::shared_ptr<GraphNode>& gn,
		const Vec2r& position,
		real_t size,
		color_t color) noexcept;

	void draw3D(const Graphics& graphics, real_t size, color_t color) const noexcept;
	static void drawNode3D(
		const Graphics& graphics,
		const std::shared_ptr<GraphNode>& gn,
		const Vec2<uint8_t>& tile,
		real_t size,
		color_t color) noexcept;
	static void drawWWall(
		const Graphics& graphics,
		const Vec2<uint8_t>& tile,
		real_t size,
		color_t color) noexcept;
	static void drawEWall(
		const Graphics& graphics,
		const Vec2<uint8_t>& tile,
		real_t size,
		color_t color) noexcept;
	static void drawNWall(
		const Graphics& graphics,
		const Vec2<uint8_t>& tile,
		real_t size,
		color_t color) noexcept;
	static void drawSWall(
		const Graphics& graphics,
		const Vec2<uint8_t>& tile,
		real_t size,
		color_t color) noexcept;
	static void drawWEWall(
		const Graphics& graphics,
		const Vec2<uint8_t>& tile,
		real_t size,
		color_t color) noexcept;
	static void drawNSWall(
		const Graphics& graphics,
		const Vec2<uint8_t>& tile,
		real_t size,
		color_t color) noexcept;
	static void drawXWall(
		const Graphics& graphics,
		const Vec2r& position,
		const Vec2r& size,
		color_t color) noexcept;
	static void drawZWall(
		const Graphics& graphics,
		const Vec2r& position,
		const Vec2r& size,
		color_t color) noexcept;

	friend struct Graphics;
};
