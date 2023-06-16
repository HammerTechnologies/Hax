#include "core.h"
#include "logger.h"
#include "gfx/_internal/graphics_driver.h"

Core::Core(const Vec2<uint16_t>& size, bool fullscreen, const Logger& logger) noexcept
: m_logger{logger},
	m_context{logger},
	m_window{
		m_context.createWindow(size, fullscreen),
		[this](ContextWindow* win){ m_context.destroyWindow(*win); }
	},
	m_screen{m_context, m_window, logger},
	m_input{m_context, m_window},
	m_gfxDriver{m_context.getGlGetProcAddressFunc(), logger},
	m_graphics{m_gfxDriver, logger} {
	m_logger.info("Core services initializated.");
}

Core::~Core() noexcept {
	m_logger.info("Core services deinitializing...");
}

void Core::terminate() noexcept {
	ContextDriver::terminate();
}