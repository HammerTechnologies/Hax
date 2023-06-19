#pragma once

#include <memory>
#include "maze/generator.h"
#include "ngn/gfx/color.h"
#include "ngn/mth/mat4.h"
#include "ngn/mth/vec2.h"

struct Graph;

namespace ngn {
	struct Graphics;
	struct Texture;
}

struct Level {
	Level(
		const ngn::Vec2<uint8_t>& size,
		uint32_t seed,
		const std::shared_ptr<const ngn::Texture>& tex,
		const ngn::Graphics& graphics) noexcept
	: m_graphics{graphics},
		m_tex{tex},
		m_maze{generateMaze(size.x(), size.y(), seed)} {}

	ngn::Vec2<uint8_t> size() const noexcept { return {m_maze->getWidth(), m_maze->getHeight()}; }

	void draw2D(const ngn::Vec2r& position, ngn::real_t size, ngn::color_t color) const noexcept;
	void draw3D(ngn::real_t size, ngn::color_t color) const noexcept;
private:
	const ngn::Graphics& m_graphics;
	const std::shared_ptr<const ngn::Texture> m_tex;
	const std::unique_ptr<Graph> m_maze;

	void drawNode2D(
		const std::shared_ptr<GraphNode>& gn,
		const ngn::Vec2r& position,
		ngn::real_t size,
		ngn::color_t color) const noexcept;

	void drawNode3D(
		const std::shared_ptr<GraphNode>& gn,
		const ngn::Vec2<uint8_t>& tile,
		ngn::real_t size,
		ngn::color_t color) const noexcept;

	void drawWWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept;
	void drawEWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept;
	void drawNWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept;
	void drawSWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept;
	void drawWEWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept;
	void drawNSWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept;
	void drawXWall(const ngn::Vec2r& position, const ngn::Vec2r& size, ngn::color_t color) const noexcept;
	void drawZWall(const ngn::Vec2r& position, const ngn::Vec2r& size, ngn::color_t color) const noexcept;
};
