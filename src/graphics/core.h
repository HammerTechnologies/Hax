#pragma once

#include <memory>
#include "graphics.h"
#include "input.h"
#include "screen.h"

struct GLFWwindow;
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
	std::shared_ptr<GLFWwindow> m_window;
	Screen m_screen;
	Input m_input;
	Graphics m_graphics;
};
