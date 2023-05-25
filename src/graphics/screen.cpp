#include <GLFW/glfw3.h>
#include "../logger.h"
#include "screen.h"

Screen::Screen(const std::shared_ptr<GLFWwindow>& window, const Logger& logger) noexcept
: m_logger{logger},
	m_window{window},
	m_delta{0},
	m_lastTime{0},
	m_fps{0},
	m_fpsCounter{0},
	m_fpsTime{0} {
	enableContext();
	m_lastTime = glfwGetTime();
	m_logger.info("Screen initialized.");
}

Screen::~Screen() {
	m_logger.info("Screen deinitialized.");
}

void Screen::enableContext() const noexcept {
	glfwMakeContextCurrent(m_window.get());
	if (glfwGetError(NULL) != GLFW_NO_ERROR) {
		m_logger.error("Could not enable GL context.");
	}
}

uint16_t Screen::getWidth() const noexcept {
	int w;
	glfwGetFramebufferSize(m_window.get(), &w, nullptr);
	return static_cast<uint16_t>(w);
}

uint16_t Screen::getHeight() const noexcept {
	int h;
	glfwGetFramebufferSize(m_window.get(), nullptr, &h);
	return static_cast<uint16_t>(h);
}

bool Screen::isOpened() const noexcept {
	return !glfwWindowShouldClose(m_window.get());
}

void Screen::refresh() noexcept {
	// Refresh screen
	glfwSwapBuffers(m_window.get());
	glfwPollEvents();

	// Update delta
	const auto currentTime = glfwGetTime();
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
