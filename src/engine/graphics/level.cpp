#include "graphics.h"
#include "level.h"

void Level::draw2D(
	const Graphics& graphics,
	real_t x,
	real_t y,
	real_t size,
	uint32_t color) const noexcept {
	for (uint8_t tileY = 0; tileY < m_maze->getHeight(); ++tileY) {
		for (uint8_t tileX = 0; tileX < m_maze->getWidth(); ++tileX) {
			drawNode2D(
				graphics,
				m_maze->getNodeAt(tileX, tileY),
				x + tileX * size,
				y + tileY * size,
				size,
				color);
		}
	}
}

void Level::drawNode2D(
	const Graphics& graphics,
	const std::shared_ptr<GraphNode>& gn,
	real_t x,
	real_t y,
	real_t size,
	uint32_t color) noexcept {
	const auto half = size / 2;
	if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		graphics.drawRect(x, y + half, half, 1, color);
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth())	{
		graphics.drawRect(x + half, y + half, half, 1, color);
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		graphics.drawRect(x + half, y, 1, half, color);
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		graphics.drawRect(x + half, y + half, 1, half, color);
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		graphics.drawRect(x, y + half, size, 1, color);
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		graphics.drawRect(x + half, y, 1, size, color);
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		graphics.drawRect(x + half, y + half, half, 1, color);
		graphics.drawRect(x + half, y + half, 1, half, color);
	} else if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		graphics.drawRect(x, y + half, half, 1, color);
		graphics.drawRect(x + half, y + half, 1, half, color);
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		graphics.drawRect(x + half, y + half, half, 1, color);
		graphics.drawRect(x + half, y, 1, half, color);
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		graphics.drawRect(x, y + half, half, 1, color);
		graphics.drawRect(x + half, y, 1, half, color);
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		graphics.drawRect(x + half, y + half, half, 1, color);
		graphics.drawRect(x + half, y, 1, size, color);
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		graphics.drawRect(x, y + half, half, 1, color);
		graphics.drawRect(x + half, y, 1, size, color);
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		graphics.drawRect(x, y + half, size, 1, color);
		graphics.drawRect(x + half, y + half, 1, half, color);
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		graphics.drawRect(x, y + half, size, 1, color);
		graphics.drawRect(x + half, y, 1, half, color);
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		graphics.drawRect(x, y, size, 1, color);
		graphics.drawRect(x + half, y, 1, size, color);
	}
}

void Level::draw3D(const Graphics& graphics, real_t size, uint32_t color) const noexcept {
	for (uint8_t y = 0; y < m_maze->getHeight(); ++y) {
		for (uint8_t x = 0; x < m_maze->getWidth(); ++x) {
			drawNode3D(graphics, m_maze->getNodeAt(x, y), x, y, size, color);
		}
	}
}

void Level::drawNode3D(
	const Graphics& graphics,
	const std::shared_ptr<GraphNode>& gn,
	uint16_t tileX,
	uint16_t tileY,
	real_t size,
	uint32_t color) noexcept {
	const auto dark = Color::multiply(color, 0.75f);
	if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		drawWWall(graphics, tileX, tileY, size, color);
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth())	{
		drawEWall(graphics, tileX, tileY, size, color);
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		drawNWall(graphics, tileX, tileY, size, dark);
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		drawSWall(graphics, tileX, tileY, size, dark);
	} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		drawWEWall(graphics, tileX, tileY, size, color);
	} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		drawNSWall(graphics, tileX, tileY, size, dark);
	} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		drawEWall(graphics, tileX, tileY, size, color);
		drawSWall(graphics, tileX, tileY, size, dark);
	} else if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
		drawWWall(graphics, tileX, tileY, size, color);
		drawSWall(graphics, tileX, tileY, size, dark);
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		drawEWall(graphics, tileX, tileY, size, color);
		drawNWall(graphics, tileX, tileY, size, dark);
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
		drawWWall(graphics, tileX, tileY, size, color);
		drawNWall(graphics, tileX, tileY, size, dark);
	} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		drawEWall(graphics, tileX, tileY, size, color);
		drawNSWall(graphics, tileX, tileY, size, dark);
	} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
		drawWWall(graphics, tileX, tileY, size, color);
		drawNSWall(graphics, tileX, tileY, size, dark);
	} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
		drawWEWall(graphics, tileX, tileY, size, color);
		drawSWall(graphics, tileX, tileY, size, dark);
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
		drawWEWall(graphics, tileX, tileY, size, color);
		drawNWall(graphics, tileX, tileY, size, dark);
	} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
		drawWEWall(graphics, tileX, tileY, size, color);
		drawNSWall(graphics, tileX, tileY, size, dark);
	}
}

void Level::drawWWall(
	const Graphics& graphics,
	uint16_t tileX,
	uint16_t tileY,
	real_t size,
	uint32_t color) noexcept {
	const auto half = size / 2;
	drawXWall(graphics, tileX * size, tileY * size + half, half, size, color);
}

void Level::drawEWall(
	const Graphics& graphics,
	uint16_t tileX,
	uint16_t tileY,
	real_t size,
	uint32_t color) noexcept {
	const auto half = size / 2;
	drawXWall(graphics, tileX * size + half, tileY * size + half, half, size, color);
}

void Level::drawNWall(
	const Graphics& graphics,
	uint16_t tileX,
	uint16_t tileY,
	real_t size,
	uint32_t color) noexcept {
	const auto half = size / 2;
	drawZWall(graphics, tileX * size + half, tileY * size + half, half, size, color);
}

void Level::drawSWall(
	const Graphics& graphics,
	uint16_t tileX,
	uint16_t tileY,
	real_t size,
	uint32_t color) noexcept {
	const auto half = size / 2;
	drawZWall(graphics, tileX * size + half, tileY * size, half, size, color);
}

void Level::drawWEWall(
	const Graphics& graphics,
	uint16_t tileX,
	uint16_t tileY,
	real_t size,
	uint32_t color) noexcept {
	const auto half = size / 2;
	drawXWall(graphics, tileX * size, tileY * size + half, size, size, color);
}

void Level::drawNSWall(
	const Graphics& graphics,
	uint16_t tileX,
	uint16_t tileY,
	real_t size,
	uint32_t color) noexcept {
	const auto half = size / 2;
	drawZWall(graphics, tileX * size + half, tileY * size, size, size, color);
}

void Level::drawXWall(
	const Graphics& graphics,
	real_t x,
	real_t z,
	real_t width,
	real_t height,
	uint32_t color) noexcept {
	const auto transform = Mat4r::transform(
		Vec3r{x, 0, z},
		Quatr{},
		Vec3r{width, height, 1});
	graphics.drawQuad(transform, color);
}

void Level::drawZWall(
	const Graphics& graphics,
	real_t x,
	real_t z,
	real_t width,
	real_t height,
	uint32_t color) noexcept {
	const auto transform = Mat4r::transform(
		Vec3r{x, 0, z},
		Quatr::fromEuler(Vec3r{0, M_PI_2, 0}),
		Vec3r{width, height, 1});
	graphics.drawQuad(transform, color);
}
