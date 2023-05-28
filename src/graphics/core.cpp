#include "../logger.h"
#include "core.h"

Core::Core(uint16_t width, uint16_t height, bool fullscreen, const Logger& logger) noexcept
: m_logger{logger},
	m_context{logger},
	m_window{
		m_context.createWindow(width, height, fullscreen),
		[this](ContextWindow* win){ m_context.destroyWindow(*win); }
	},
	m_screen{m_context, m_window, logger},
	m_input{m_context, m_window},
	m_graphics{m_context.getGlGetProcAddressFunc(), logger} {
	m_logger.info("Core services initializated.");
}

Core::~Core() noexcept {
	m_logger.info("Core services deinitializing...");
}

void Core::terminate() noexcept {
	ContextDriver::terminate();
}