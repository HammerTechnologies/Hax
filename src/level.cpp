#include "ngn/gfx/graphics.h"
#include "level.h"

void Level::draw2D(const ngn::Vec2r& position, ngn::real_t size, ngn::color_t color) const noexcept {
	for (auto tileY = 0; tileY < m_maze->getHeight(); ++tileY) {
		for (auto tileX = 0; tileX < m_maze->getWidth(); ++tileX) {
			drawNode2D(
				m_maze->getNodeAt(tileX, tileY),
				position + ngn::Vec2r(tileX, tileY) * size,
				size,
				color);
		}
	}
}

void Level::draw3D(ngn::real_t size, ngn::color_t color) const noexcept {
	for (auto tileY = uint8_t {0}; tileY < m_maze->getHeight(); ++tileY) {
		for (auto tileX = uint8_t {0}; tileX < m_maze->getWidth(); ++tileX) {
			drawNode3D(
				m_maze->getNodeAt(tileX, tileY),
				{tileX, uint8_t(m_maze->getHeight() - tileY - 1)},
				size,
				color);
		}
	}
}

void Level::drawNode2D(
	const std::shared_ptr<GraphNode>& gn,
	const ngn::Vec2r& position,
	ngn::real_t size,
	ngn::color_t color) const noexcept {
	const auto half = size / 2;
	if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		m_graphics.drawRect({position.x(), position.y() + half}, {half, 1}, color);
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth())	{
		m_graphics.drawRect(position + half, {half, 1}, color);
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		m_graphics.drawRect({position.x() + half, position.y()}, {1, half}, color);
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		m_graphics.drawRect(position + half, {1, half}, color);
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		m_graphics.drawRect({position.x(), position.y() + half}, {size, 1}, color);
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		m_graphics.drawRect({position.x() + half, position.y()}, {1, size}, color);
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		m_graphics.drawRect(position + half, {half, 1}, color);
		m_graphics.drawRect(position + half, {1, half}, color);
	} else if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		m_graphics.drawRect({position.x(), position.y() + half}, {half, 1}, color);
		m_graphics.drawRect(position + half, {1, half}, color);
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		m_graphics.drawRect(position + half, {half, 1}, color);
		m_graphics.drawRect({position.x() + half, position.y()}, {1, half}, color);
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		m_graphics.drawRect({position.x(), position.y() + half}, {half, 1}, color);
		m_graphics.drawRect({position.x() + half, position.y()}, {1, half}, color);
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		m_graphics.drawRect(position + half, {half, 1}, color);
		m_graphics.drawRect({position.x() + half, position.y()}, {1, size}, color);
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		m_graphics.drawRect({position.x(), position.y() + half}, {half, 1}, color);
		m_graphics.drawRect({position.x() + half, position.y()}, {1, size}, color);
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		m_graphics.drawRect({position.x(), position.y() + half}, {size, 1}, color);
		m_graphics.drawRect(position + half, {1, half}, color);
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		m_graphics.drawRect({position.x(), position.y() + half}, {size, 1}, color);
		m_graphics.drawRect({position.x() + half, position.y()}, {1, half}, color);
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		m_graphics.drawRect(position, {size, 1}, color);
		m_graphics.drawRect({position.x() + half, position.y()}, {1, size}, color);
	}
}

void Level::drawNode3D(
	const std::shared_ptr<GraphNode>& gn,
	const ngn::Vec2<uint8_t>& tile,
	ngn::real_t size,
	ngn::color_t color) const noexcept {
	const auto dark = ngn::Color::multiply(color, 0.75f);
	if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		drawWWall(tile, size, color);
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth())	{
		drawEWall(tile, size, color);
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		drawNWall(tile, size, dark);
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		drawSWall(tile, size, dark);
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		drawWEWall(tile, size, color);
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		drawNSWall(tile, size, dark);
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		drawEWall(tile, size, color);
		drawSWall(tile, size, dark);
	} else if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		drawWWall(tile, size, color);
		drawSWall(tile, size, dark);
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		drawEWall(tile, size, color);
		drawNWall(tile, size, dark);
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		drawWWall(tile, size, color);
		drawNWall(tile, size, dark);
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		drawEWall(tile, size, color);
		drawNSWall(tile, size, dark);
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		drawWWall(tile, size, color);
		drawNSWall(tile, size, dark);
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		drawWEWall(tile, size, color);
		drawSWall(tile, size, dark);
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		drawWEWall(tile, size, color);
		drawNWall(tile, size, dark);
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		drawWEWall(tile, size, color);
		drawNSWall(tile, size, dark);
	}
}

void Level::drawWWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept {
	const auto half = size / 2;
	drawXWall({tile.x() * size, tile.y() * size + half}, {half, size}, color);
}

void Level::drawEWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept {
	const auto half = size / 2;
	drawXWall({tile.x() * size + half, tile.y() * size + half}, {half, size}, color);
}

void Level::drawNWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept {
	const auto half = size / 2;
	drawZWall({tile.x() * size + half, (tile.y() + 1) * size}, {half, size}, color);
}

void Level::drawSWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept {
	const auto half = size / 2;
	drawZWall({tile.x() * size + half, tile.y() * size + half}, {half, size}, color);
}

void Level::drawWEWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept {
	const auto half = size / 2;
	drawXWall({tile.x() * size, tile.y() * size + half}, {size, size}, color);
}

void Level::drawNSWall(const ngn::Vec2<uint8_t>& tile, ngn::real_t size, ngn::color_t color) const noexcept {
	const auto half = size / 2;
	drawZWall({tile.x() * size + half, (tile.y() + 1) * size}, {size, size}, color);
}

void Level::drawXWall(const ngn::Vec2r& position, const ngn::Vec2r& size, ngn::color_t color) const noexcept {
	const auto transform = ngn::Mat4r::transform(
		ngn::Vec3r{position.x(), 0, position.y()},
		ngn::Quatr{},
		ngn::Vec3r{size, 1});
	m_graphics.drawQuad(transform, m_tex.get(), color);
}

void Level::drawZWall(const ngn::Vec2r& position, const ngn::Vec2r& size, ngn::color_t color) const noexcept {
	const auto transform = ngn::Mat4r::transform(
		{position.x(), 0, position.y()},
		ngn::Quatr::fromEuler(ngn::Vec3r{0, M_PI_2, 0}),
		{size, 1});
	m_graphics.drawQuad(transform, m_tex.get(), color);
}
