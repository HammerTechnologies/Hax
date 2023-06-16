#pragma once

#include <memory>
#include "gfx/_internal/context_driver.h"
#include "gfx/_internal/graphics_driver.h"
#include "gfx/graphics.h"
#include "gfx/screen.h"
#include "io/input.h"
#include "mth/vec2.h"

struct Logger;

struct Core {
	Core(const Vec2<uint16_t>& size, bool fullscreen, const Logger& logger) noexcept;
	~Core() noexcept;

	constexpr const Graphics& graphics() const noexcept { return m_graphics; }
	constexpr const Input& input() const noexcept { return m_input; }
	constexpr const Screen& screen() const noexcept { return m_screen; }
	constexpr Graphics& graphics() noexcept { return m_graphics; }
	constexpr Screen& screen() noexcept { return m_screen; }

	static void terminate() noexcept;
private:
	const Logger& m_logger;
	ContextDriver m_context;
	std::shared_ptr<ContextWindow> m_window;
	Screen m_screen;
	Input m_input;
	GraphicsDriver m_gfxDriver;
	Graphics m_graphics;
};
