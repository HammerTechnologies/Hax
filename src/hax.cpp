#include <memory>
#include <sstream>
#include "dir.h"
#include "engine/core.h"
#include "engine/game.h"
#include "engine/graphics/font.h"
#include "engine/graphics/level.h"
#include "engine/graphics/texture.h"
#include "engine/graphics/viewer.h"
#include "engine/logger.h"

struct Hax : Game {
	Hax() noexcept
	: m_core{{640, 360}, false, m_logger},
		m_viewer{
			{0, 8, -5},
			{},
			{0, 0},
			m_core.getScreen().getSize(),
		},
		m_level{{16, 16}, 0},
		m_font{nullptr},
		m_tex{nullptr} {
			changeDir(exeDir() + "/assets");
			m_font = m_core.getGraphics().loadFont("Minecraft.ttf", 16);
			m_tex = m_core.getGraphics().loadTexture("mockup.png");
		}

	virtual bool update() noexcept override {
		auto& graphics = m_core.getGraphics();
		auto& input = m_core.getInput();
		auto& screen = m_core.getScreen();

		if (!screen.isOpened() || input.isKeyDown(Key::ESC)) {
			return false;
		}

		if (input.isKeyDown(Key::LEFT)) { m_viewer.euler(m_viewer.euler() - Vec3r {0, 180 * screen.getDelta(), 0}); }
		if (input.isKeyDown(Key::RIGHT)) { m_viewer.euler(m_viewer.euler() + Vec3r {0, 180 * screen.getDelta(), 0}); }
		if (input.isKeyDown(Key::UP)) { m_viewer.move(Vec3r{0, 0, 16 * screen.getDelta()}); }
		if (input.isKeyDown(Key::DOWN)) { m_viewer.move(Vec3r{0, 0, -16 * screen.getDelta()}); }

		auto ss = std::ostringstream {};
		ss << screen.getSize().x() << "x" << screen.getSize().y() << " @ " << screen.getFps() << " FPS";

		m_viewer.viewportSize(screen.getSize());

		graphics.setup3D(m_viewer);
		graphics.cls();
		graphics.drawLevel3D(m_level, 16, Color::WHITE);

		graphics.setup2D({0, 0}, screen.getSize());
		//graphics.drawTexture(m_tex.get(), 0, 0, screen.getWidth(), screen.getHeight());
		graphics.drawLevel2D(m_level, {16, 32}, 16, Color::ORANGE);
		graphics.drawRect(
			{12 + m_viewer.position().x(), 28 + m_level.getSize().y() * 16 - m_viewer.position().z()},
			{8, 8},
			Color::RED);
		graphics.drawText(m_font.get(), ss.str(), {14, 12}, Color::RED);

		screen.refresh();

		return true;
	}

	virtual void finish() noexcept override;
private:
	Logger m_logger;
	Core m_core;
	Viewer m_viewer;
	Level m_level;
	std::unique_ptr<Font> m_font;
	std::unique_ptr<Texture> m_tex;
};

std::unique_ptr<Hax> g_hax = std::make_unique<Hax>();

void Hax::finish() noexcept {
	g_hax = nullptr;
}
