#pragma once

#include <functional>
#include <memory>
#include "hax_inputs.h"
#include "level.h"
#include "ngn/core.h"
#include "ngn/gfx/font.h"
#include "ngn/gfx/texture.h"
#include "ngn/gfx/viewer.h"

struct HaxData {
	ngn::real_t delta() const noexcept { return m_core->screen().delta(); }
	const ngn::Font& font() const noexcept { return *m_font; }
	uint32_t fps() const noexcept { return m_core->screen().fps(); }
	const HaxInputs& inputs() const noexcept { return m_inputs; }
	const Level& level() const noexcept { return *m_level; }
	ngn::Vec2<uint16_t> screenSize() const noexcept { return m_core->screen().size(); }
	const ngn::Texture& sheet() const noexcept { return *m_sheet; }
	const ngn::Viewer& viewer() const noexcept { return m_viewer; }

	Level& level() noexcept { return *m_level; }
	ngn::Viewer& viewer() noexcept { return m_viewer; }

	void update() noexcept {
		m_inputs.update(m_core->input());
	}

	void finish() noexcept {
		m_font = nullptr;
		m_level = nullptr;
		m_core = nullptr;
	}
private:
	std::unique_ptr<ngn::Core> m_core = std::make_unique<ngn::Core>(
		ngn::Vec2<uint16_t>{640, 360},
		false);
	HaxInputs m_inputs {};
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
	std::unique_ptr<ngn::Texture> m_sheet { m_core->graphics().loadTexture("textures/wall001.png") };

	friend void init() noexcept;
	friend bool update() noexcept;
};
