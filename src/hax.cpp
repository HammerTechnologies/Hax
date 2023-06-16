#include <memory>
#include <sstream>
#include "dir.h"
#include "ngn/core.h"
#include "ngn/game.h"
#include "ngn/gfx/font.h"
#include "ngn/gfx/level.h"
#include "ngn/gfx/texture.h"
#include "ngn/gfx/viewer.h"
#include "ngn/logger.h"

struct Hax : Game {
	Hax() noexcept
	: m_core{{640, 360}, false, m_logger},
		m_viewer{
			{0, 8, -5},
			{},
			{0, 0},
			m_core.screen().size(),
		},
		m_level{{16, 16}, 0},
		m_font{nullptr},
		m_tex{nullptr} {
			changeDir(exeDir() + "/assets");
			m_font = m_core.graphics().loadFont("Minecraft.ttf", 16);
			m_tex = m_core.graphics().loadTexture("mockup.png");
		}

	virtual bool update() noexcept override {
		auto& graphics = m_core.graphics();
		auto& input = m_core.input();
		auto& screen = m_core.screen();

		if (!screen.isOpened() || input.isKeyDown(Key::ESC)) {
			return false;
		}

		if (input.isKeyDown(Key::LEFT)) { m_viewer.euler(m_viewer.euler() - Vec3r {0, 180 * screen.delta(), 0}); }
		if (input.isKeyDown(Key::RIGHT)) { m_viewer.euler(m_viewer.euler() + Vec3r {0, 180 * screen.delta(), 0}); }
		if (input.isKeyDown(Key::UP)) { m_viewer.move(Vec3r{0, 0, 16 * screen.delta()}); }
		if (input.isKeyDown(Key::DOWN)) { m_viewer.move(Vec3r{0, 0, -16 * screen.delta()}); }

		auto ss = std::ostringstream {};
		ss << screen.size().x() << "x" << screen.size().y() << " @ " << screen.fps() << " FPS";

		m_viewer.viewportSize(screen.size());

		graphics.setup3D(m_viewer);
		graphics.cls();
		graphics.drawLevel3D(m_level, 16, Color::WHITE);

		graphics.setup2D({0, 0}, screen.size());
		//graphics.drawTexture(m_tex.get(), 0, 0, screen.getWidth(), screen.getHeight());
		graphics.drawLevel2D(m_level, {16, 32}, 16, Color::ORANGE);
		graphics.drawRect(
			{12 + m_viewer.position().x(), 28 + m_level.size().y() * 16 - m_viewer.position().z()},
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

auto g_hax = std::make_unique<Hax>();

void Hax::finish() noexcept {
	g_hax = nullptr;
}
