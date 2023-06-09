#pragma once

#include <memory>
#include "graphics/graphics.h"
#include "graphics/input.h"
#include "graphics/internal/context_driver.h"
#include "graphics/internal/graphics_driver.h"
#include "graphics/screen.h"

struct Logger;

struct Core {
	Core(uint16_t width, uint16_t height, bool fullscreen, const Logger& logger) noexcept;
	~Core() noexcept;

	constexpr const Graphics& getGraphics() const noexcept { return m_graphics; }
	constexpr const Input& getInput() const noexcept { return m_input; }
	constexpr const Screen& getScreen() const noexcept { return m_screen; }
	constexpr Graphics& getGraphics() noexcept { return m_graphics; }
	constexpr Screen& getScreen() noexcept { return m_screen; }

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
