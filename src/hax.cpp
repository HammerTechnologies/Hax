#include <memory>
#include <sstream>
#include "dir.h"
#include "level.h"
#include "ngn/core.h"
#include "ngn/gfx/font.h"
#include "ngn/gfx/texture.h"
#include "ngn/gfx/viewer.h"
#include "ngn/logger.h"

struct Hax {
	Hax() noexcept
	: m_core{{640, 360}, false, m_logger},
		m_viewer{
			{0, 8, -5},
			{},
			{0, 0},
			m_core.screen().size(),
		},
		m_font{nullptr},
		m_tex{nullptr},
		m_level{nullptr} {
		changeDir(exeDir() + "/assets");
		m_font = m_core.graphics().loadFont("Minecraft.ttf", 16);
		m_tex = m_core.graphics().loadTexture("textures/wall001.png");
		m_level = std::make_unique<Level>(ngn::Vec2<uint8_t>{16, 16}, 0, m_tex, m_core.graphics());
	}

	bool update() noexcept {
		auto& graphics = m_core.graphics();
		auto& input = m_core.input();
		auto& screen = m_core.screen();

		if (!screen.isOpened() || input.isKeyDown(ngn::Key::ESC)) {
			return false;
		}

		if (input.isKeyDown(ngn::Key::LEFT)) { m_viewer.euler(m_viewer.euler() - ngn::Vec3r {0, 180 * screen.delta(), 0}); }
		if (input.isKeyDown(ngn::Key::RIGHT)) { m_viewer.euler(m_viewer.euler() + ngn::Vec3r {0, 180 * screen.delta(), 0}); }
		if (input.isKeyDown(ngn::Key::UP)) { m_viewer.move(ngn::Vec3r{0, 0, 16 * screen.delta()}); }
		if (input.isKeyDown(ngn::Key::DOWN)) { m_viewer.move(ngn::Vec3r{0, 0, -16 * screen.delta()}); }

		auto ss = std::ostringstream {};
		ss << screen.size().x() << "x" << screen.size().y() << " @ " << screen.fps() << " FPS";

		m_viewer.viewportSize(screen.size());

		graphics.setup3D(m_viewer);
		graphics.cls();
		m_level->draw3D(16, ngn::Color::WHITE);

		graphics.setup2D({0, 0}, screen.size());
		//graphics.drawTexture(m_tex.get(), 0, 0, screen.getWidth(), screen.getHeight());
		m_level->draw2D({16, 32}, 16, ngn::Color::ORANGE);
		graphics.drawRect(
			{12 + m_viewer.position().x(), 28 + m_level->size().y() * 16 - m_viewer.position().z()},
			{8, 8},
			ngn::Color::RED);
		graphics.drawText(m_font.get(), ss.str(), {14, 12}, ngn::Color::RED);

		screen.refresh();

		return true;
	}
private:
	ngn::Logger m_logger;
	ngn::Core m_core;
	ngn::Viewer m_viewer;
	std::unique_ptr<ngn::Font> m_font;
	std::shared_ptr<ngn::Texture> m_tex;
	std::unique_ptr<Level> m_level;
};

auto g_hax = std::make_unique<Hax>();

void init() noexcept {
}

bool update() noexcept {
	return g_hax->update();
}

void finish() noexcept {
	g_hax = nullptr;
}
