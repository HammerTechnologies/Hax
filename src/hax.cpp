#include <memory>
#include <sstream>
#include "dir.h"
#include "engine/core.h"
#include "engine/graphics/font.h"
#include "engine/graphics/texture.h"
#include "engine/graphics/viewer.h"
#include "engine/logger.h"
#include "engine/maze/generator.h"

struct Hax {
	Hax() noexcept
	: m_core{640, 360, false, m_logger},
		m_viewer{
			Vec3r{0, 0, -5},
			Vec3r{},
			0,
			0,
			m_core.getScreen().getWidth(),
			m_core.getScreen().getHeight()
		},
		m_maze{generateMaze(16, 16, 0)},
		m_font{nullptr},
		m_tex{nullptr},
		m_yaw{0} {
			changeDir(exeDir() + "/assets");
			m_font = m_core.getGraphics().loadFont("Minecraft.ttf", 16);
			m_tex = m_core.getGraphics().loadTexture("mockup.png");
		}

	bool update() noexcept {
		if (m_core.getInput().isKeyDown(Key::ESC)) {
			return false;
		}

		std::ostringstream ss;
		ss << m_core.getScreen().getWidth() << "x" << m_core.getScreen().getHeight() << " @ " << m_core.getScreen().getFps() << " FPS";

		m_yaw += M_PI * m_core.getScreen().getDelta();
		m_viewer.m_viewportWidth = m_core.getScreen().getWidth();
		m_viewer.m_viewportHeight = m_core.getScreen().getHeight();

		m_core.getGraphics().setup2D(0, 0, m_core.getScreen().getWidth(), m_core.getScreen().getHeight());
		m_core.getGraphics().cls();
		m_core.getGraphics().drawTexture(*m_tex, 0, 0, m_core.getScreen().getWidth(), m_core.getScreen().getHeight());
		m_core.getGraphics().drawText(*m_font, ss.str(), 14, 12);

		for (uint8_t y = 0; y < m_maze->getHeight(); y++) {
			for (uint8_t x = 0; x < m_maze->getWidth(); x++) {
				drawNode(m_maze->getNodeAt(x, y), x + 2, y + 2, 16, Color::YELLOW);
			}
		}

		m_core.getGraphics().setup3D(m_viewer);
		m_core.getGraphics().drawQuad(
			Mat4r::transform(
				Vec3r{},
				Quatr::fromEuler(Vec3r{0, m_yaw, 0}),
				Vec3r{1, 1, 1}),
			Color::ORANGE);
		m_core.getScreen().refresh();

		return true;
	}

	bool isScreenOpened() const noexcept {
		return m_core.getScreen().isOpened();
	}
private:
	Logger m_logger;
	Core m_core;
	Viewer m_viewer;
	std::unique_ptr<Graph> m_maze;
	std::unique_ptr<Font> m_font;
	std::unique_ptr<Texture> m_tex;
	real_t m_yaw;

	void drawNode(
		const std::shared_ptr<GraphNode>& gn,
		uint16_t tileX,
		uint16_t tileY,
		uint16_t size,
		uint32_t color) const noexcept {
		const auto half = size / 2;
		const auto& graphics = m_core.getGraphics();
		if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size + half, half, 1, color);
		} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth())	{
			graphics.drawRect(tileX * size + half, tileY * size + half, half, 1, color);
		} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
			graphics.drawRect(tileX * size + half, tileY * size, 1, half, color);
		} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
			graphics.drawRect(tileX * size + half, tileY * size + half, 1, half, color);
		} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size + half, size, 1, color);
		} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
			graphics.drawRect(tileX * size + half, tileY * size, 1, size, color);
		} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
			graphics.drawRect(tileX * size + half, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size + half, 1, half, color);
		} else if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size + half, 1, half, color);
		} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
			graphics.drawRect(tileX * size + half, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, half, color);
		} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, half, color);
		} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
			graphics.drawRect(tileX * size + half, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, size, color);
		} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
			graphics.drawRect(tileX * size, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, size, color);
		} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
			graphics.drawRect(tileX * size, tileY * size + half, size, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size + half, 1, half, color);
		} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
			graphics.drawRect(tileX * size, tileY * size + half, size, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, half, color);
		} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size, size, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, size, color);
		}
	}
};

std::unique_ptr<Hax> g_hax = nullptr;

void init() noexcept {
	g_hax = std::make_unique<Hax>();
}

bool update() noexcept {
	return g_hax->update();
}

void finish() noexcept {
	g_hax = nullptr;
}
