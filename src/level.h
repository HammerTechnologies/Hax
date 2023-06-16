#pragma once

#include <memory>
#include "maze/generator.h"
#include "ngn/gfx/color.h"
#include "ngn/mth/mat4.h"
#include "ngn/mth/vec2.h"

struct Graph;
struct Graphics;

struct Level {
	Level(const Vec2<uint8_t>& size, uint32_t seed, const Graphics& graphics) noexcept
	: m_graphics{graphics}, m_maze{generateMaze(size.x(), size.y(), seed)} {}

	Vec2<uint8_t> size() const noexcept { return {m_maze->getWidth(), m_maze->getHeight()}; }

	void draw2D(const Vec2r& position, real_t size, color_t color) const noexcept;
	void draw3D(real_t size, color_t color) const noexcept;
private:
	const Graphics& m_graphics;
	std::unique_ptr<Graph> m_maze;

	void drawNode2D(
		const std::shared_ptr<GraphNode>& gn,
		const Vec2r& position,
		real_t size,
		color_t color) const noexcept;

	void drawNode3D(
		const std::shared_ptr<GraphNode>& gn,
		const Vec2<uint8_t>& tile,
		real_t size,
		color_t color) const noexcept;

	void drawWWall(const Vec2<uint8_t>& tile, real_t size, color_t color) const noexcept;
	void drawEWall(const Vec2<uint8_t>& tile, real_t size, color_t color) const noexcept;
	void drawNWall(const Vec2<uint8_t>& tile, real_t size, color_t color) const noexcept;
	void drawSWall(const Vec2<uint8_t>& tile, real_t size, color_t color) const noexcept;
	void drawWEWall(const Vec2<uint8_t>& tile, real_t size, color_t color) const noexcept;
	void drawNSWall(const Vec2<uint8_t>& tile, real_t size, color_t color) const noexcept;
	void drawXWall(const Vec2r& position, const Vec2r& size, color_t color) const noexcept;
	void drawZWall(const Vec2r& position, const Vec2r& size, color_t color) const noexcept;
};
