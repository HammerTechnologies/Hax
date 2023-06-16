#include "../logger.h"
#include "screen.h"

Screen::Screen(const ContextDriver& context, const std::shared_ptr<ContextWindow>& window, const Logger& logger) noexcept
: m_context{context},
	m_logger{logger},
	m_window{window},
	m_delta{0},
	m_lastTime{0},
	m_fps{0},
	m_fpsCounter{0},
	m_fpsTime{0} {
	enableContext();
	m_lastTime = context.getTime();
	m_logger.info("Screen initialized.");
}

Screen::~Screen() {
	m_logger.info("Screen deinitialized.");
}

void Screen::enableContext() const noexcept {
	m_context.enableWindowContext(*m_window);
}

Vec2<uint16_t> Screen::size() const noexcept {
	return m_context.getWindowSize(*m_window);
}

bool Screen::isOpened() const noexcept {
	return m_context.isWindowOpened(*m_window);
}

void Screen::refresh() noexcept {
	// Refresh screen
	m_context.refreshWindow(*m_window);

	// Update delta
	const auto currentTime = m_context.getTime();
	m_delta = static_cast<real_t>(currentTime - m_lastTime);
	m_lastTime = currentTime;

	// Update FPS
	++m_fpsCounter;
	m_fpsTime += m_delta;
	if (m_fpsTime >= 1) {
		m_fps = m_fpsCounter;
		m_fpsCounter = 0;
		m_fpsTime -= 1;
	}
}
