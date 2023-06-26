#pragma once

#include <memory>
#include "_prv/context_driver.h"
#include "_prv/graphics_driver.h"
#include "gfx/graphics.h"
#include "gfx/screen.h"
#include "io/input.h"
#include "logger.h"
#include "mth/vec2.h"

namespace ngn {

struct Logger;

struct Core {
	Core(const Vec2<uint16_t>& size, bool fullscreen) noexcept;
	~Core() noexcept;

	constexpr const Graphics& graphics() const noexcept { return m_graphics; }
	constexpr const Input& input() const noexcept { return m_input; }
	constexpr const Logger& logger() const noexcept { return m_logger; }
	constexpr const Screen& screen() const noexcept { return m_screen; }
	constexpr Graphics& graphics() noexcept { return m_graphics; }
	constexpr Screen& screen() noexcept { return m_screen; }

	static void terminate() noexcept;
private:
	Logger m_logger;
	prv::ContextDriver m_context;
	std::shared_ptr<prv::ContextWindow> m_window;
	prv::GraphicsDriver m_gfxDriver;
	Screen m_screen;
	Input m_input;
	Graphics m_graphics;
};

} // namespace ngn
