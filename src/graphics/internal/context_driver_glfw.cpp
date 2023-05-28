#include <cmath>
#include <sstream>
#include <GLFW/glfw3.h>
#include "../../logger.h"
#include "context_driver.h"

ContextDriver::ContextDriver(const Logger& logger) noexcept
: m_logger(logger) {
	if (glfwInit() != GLFW_TRUE) {
		m_logger.error("Could not initialize GLFW.");
	} else {
		int32_t major, minor, rev;
		glfwGetVersion(&major, &minor, &rev);
		std::ostringstream ss;
		ss << "GLFW version " << major << "." << minor << "." << rev << ".";
		m_logger.info(ss.str());
	}
}

ContextWindow* ContextDriver::createWindow(uint16_t width, uint16_t height, bool fullscreen) const noexcept {
	ContextWindow* win = glfwCreateWindow(
		width,
		height,
		"Hax",
		fullscreen ? glfwGetPrimaryMonitor() : nullptr,
		nullptr);
	if (!win) {
		m_logger.error("Could not create window.");
	}
	return win;
}

void ContextDriver::destroyWindow(ContextWindow& window) const noexcept {
	glfwDestroyWindow(&window);
}

void ContextDriver::enableWindowContext(ContextWindow& window) const noexcept {
	glfwMakeContextCurrent(&window);
}

uint16_t ContextDriver::getWindowWidth(ContextWindow& window) const noexcept {
	int32_t w;
	glfwGetFramebufferSize(&window, &w, nullptr);
	return static_cast<uint16_t>(w);
}

uint16_t ContextDriver::getWindowHeight(ContextWindow& window) const noexcept {
	int32_t h;
	glfwGetFramebufferSize(&window, nullptr, &h);
	return static_cast<uint16_t>(h);
}

bool ContextDriver::isWindowOpened(ContextWindow& window) const noexcept {
	return !glfwWindowShouldClose(&window);
}

void ContextDriver::refreshwindow(ContextWindow& window) const noexcept {
	glfwSwapBuffers(&window);
	glfwPollEvents();
}

real_t ContextDriver::getTime() const noexcept {
	return static_cast<real_t>(glfwGetTime());
}

void ContextDriver::setMouseVisible(ContextWindow& window, bool visible) const noexcept {
	glfwSetInputMode(&window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void ContextDriver::setMousePosition(ContextWindow& window, int32_t x, int32_t y) const noexcept {
	glfwSetCursorPos(&window, x, y);
}

int32_t ContextDriver::getMouseX(ContextWindow& window) const noexcept {
	double x;
	glfwGetCursorPos(&window, &x, nullptr);
	return static_cast<int32_t>(std::floor(x));
}

int32_t ContextDriver::getMouseY(ContextWindow& window) const noexcept {
	double y;
	glfwGetCursorPos(&window, nullptr, &y);
	return static_cast<int32_t>(std::floor(y));
}

bool ContextDriver::isMouseButtonDown(ContextWindow& window, MouseButton button) const noexcept {
	return glfwGetMouseButton(&window, static_cast<int32_t>(button)) == GLFW_PRESS;
}

bool ContextDriver::isKeyDown(ContextWindow& window, Key key) const noexcept {
	return glfwGetKey(&window, static_cast<int32_t>(key)) == GLFW_PRESS;
}

ContextDriver::GlGetProcAddress ContextDriver::getGlGetProcAddressFunc() const noexcept {
	return reinterpret_cast<GlGetProcAddress>(glfwGetProcAddress);
}

void ContextDriver::terminate() noexcept {
	glfwTerminate();
}
