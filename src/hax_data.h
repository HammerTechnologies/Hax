#pragma once

#include <functional>
#include <memory>
#include "level.h"
#include "ngn/core.h"
#include "ngn/gfx/font.h"
#include "ngn/gfx/texture.h"
#include "ngn/gfx/viewer.h"

struct HaxData {
	const ngn::Core& core() const noexcept { return *m_core; }
	const Level& level() const noexcept { return *m_level; }
	const ngn::Viewer& viewer() const noexcept { return m_viewer; }
	const ngn::Font& font() const noexcept { return *m_font; }

	ngn::Core& core() noexcept { return *m_core; }
	Level& level() noexcept { return *m_level; }
	ngn::Viewer& viewer() noexcept { return m_viewer; }

	void finish() noexcept {
		m_font = nullptr;
		m_level = nullptr;
		m_core = nullptr;
	}
private:
	std::unique_ptr<ngn::Core> m_core = std::make_unique<ngn::Core>(
		ngn::Vec2<uint16_t>{640, 360},
		false);
	std::unique_ptr<Level> m_level = std::make_unique<Level>(
		ngn::Vec2<uint8_t>{16, 16},
		0,
		m_core->graphics().loadTexture("textures/wall001.png"),
		m_core->graphics());
	ngn::Viewer m_viewer {
		{0, 8, -5},
		{},
		{0, 0},
		m_core->screen().size(),
	};
	std::unique_ptr<ngn::Font> m_font { m_core->graphics().loadFont("Minecraft.ttf", 16) };
};
