#include <GLFW/glfw3.h>
#include "screen.h"

Screen::Screen(const std::shared_ptr<GLFWwindow>& window) noexcept
: m_window{window},
	m_delta{0},
	m_lastTime{0},
	m_fps{0},
	m_fpsCounter{0},
	m_fpsTime{0} {
	enableContext();
	m_lastTime = glfwGetTime();
}

void Screen::enableContext() const noexcept {
	glfwMakeContextCurrent(m_window.get());
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
