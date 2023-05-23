#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "screen.h"

uint8_t Screen::m_initCounter = 0;

Screen::Screen(uint16_t width, uint16_t height, bool fullscreen) noexcept
: m_window{nullptr, glfwDestroyWindow},
	m_delta{0},
	m_lastTime{0},
	m_fps{0},
	m_fpsCounter{0},
	m_fpsTime{0} {
	if (m_initCounter == 0) {
		glfwInit();
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
	m_window = std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)>(
		glfwCreateWindow(width, height, "Hax", fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr),
		glfwDestroyWindow);
	enableContext();

	if (m_initCounter == 0) {
		gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	}

	m_lastTime = glfwGetTime();
	++m_initCounter;
}

Screen::~Screen() noexcept {
	--m_initCounter;
	if (m_initCounter == 0) {
		glfwTerminate();
	}
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

void Screen::setMouseVisible(bool visible) const noexcept {
	glfwSetInputMode(m_window.get(), GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void Screen::setMousePosition(int32_t x, int32_t y) const noexcept {
	glfwSetCursorPos(m_window.get(), x, y);
}

int32_t Screen::getMouseX() const noexcept {
	double x;
	glfwGetCursorPos(m_window.get(), &x, nullptr);
	return static_cast<int32_t>(std::floor(x));
}

int32_t Screen::getMouseY() const noexcept {
	double y;
	glfwGetCursorPos(m_window.get(), nullptr, &y);
	return static_cast<int32_t>(std::floor(y));
}

bool Screen::isMouseButtonDown(MouseButton button) const noexcept {
	return glfwGetMouseButton(m_window.get(), static_cast<int32_t>(button)) == GLFW_PRESS;
}

bool Screen::isKeyDown(Key key) const noexcept {
	return glfwGetKey(m_window.get(), static_cast<int32_t>(key)) == GLFW_PRESS;
}
