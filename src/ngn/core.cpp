#include "core.h"
#include "logger.h"
#include "_prv/graphics_driver.h"

namespace ngn {

Core::Core(const Vec2<uint16_t>& size, bool fullscreen) noexcept
: m_logger {},
	m_context {m_logger},
	m_window {m_context.createWindow(size, fullscreen)},
	m_gfxDriver {m_context.getGlGetProcAddressFunc(), m_logger},
	m_screen {m_context, m_window, m_logger},
	m_input {m_context, m_window},
	m_graphics {m_gfxDriver, m_logger} {
	m_logger.info("Core services initializated.");
}

Core::~Core() noexcept {
	m_logger.info("Core services deinitializing...");
}

void Core::terminate() noexcept {
	prv::ContextDriver::terminate();
}

} // namespace ngn
