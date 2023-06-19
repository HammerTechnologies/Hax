#include <cmath>
#include <sstream>
#include <GLFW/glfw3.h>
#include "../logger.h"
#include "context_driver.h"

namespace ngn::prv {

ContextWindow::~ContextWindow() {
	glfwDestroyWindow(m_win);
}

ContextDriver::ContextDriver(const Logger& logger) noexcept
: m_logger(logger) {
	if (glfwInit() != GLFW_TRUE) {
		m_logger.error("Could not initialize GLFW.");
	} else {
		auto major = 0, minor = 0, rev = 0;
		glfwGetVersion(&major, &minor, &rev);
		auto ss = std::ostringstream {};
		ss << "GLFW version " << major << "." << minor << "." << rev << ".";
		m_logger.info(ss.str());
	}
}

std::unique_ptr<ContextWindow> ContextDriver::createWindow(const Vec2<uint16_t>& size, bool fullscreen) const noexcept {
	auto win = glfwCreateWindow(
		size.x(),
		size.y(),
		"Hax",
		fullscreen ? glfwGetPrimaryMonitor() : nullptr,
		nullptr);
	if (!win) {
		m_logger.error("Could not create window.");
	}
	return std::make_unique<ContextWindow>(win);
}

void ContextDriver::enableWindowContext(ContextWindow& window) const noexcept {
	glfwMakeContextCurrent(window.m_win);
}

Vec2<uint16_t> ContextDriver::getWindowSize(ContextWindow& window) const noexcept {
	auto w = 0, h = 0;
	glfwGetFramebufferSize(window.m_win, &w, &h);
	return {uint16_t(w), uint16_t(h)};
}

bool ContextDriver::isWindowOpened(ContextWindow& window) const noexcept {
	return !glfwWindowShouldClose(window.m_win);
}

void ContextDriver::refreshWindow(ContextWindow& window) const noexcept {
	glfwSwapBuffers(window.m_win);
	glfwPollEvents();
}

real_t ContextDriver::getTime() const noexcept {
	return real_t(glfwGetTime());
}

void ContextDriver::setMouseVisible(ContextWindow& window, bool visible) const noexcept {
	glfwSetInputMode(window.m_win, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void ContextDriver::setMousePosition(ContextWindow& window, const Vec2i& position) const noexcept {
	glfwSetCursorPos(window.m_win, position.x(), position.y());
}

Vec2i ContextDriver::getMousePosition(ContextWindow& window) const noexcept {
	auto x = 0.0, y = 0.0;
	glfwGetCursorPos(window.m_win, &x, &y);
	return {int32_t(std::floor(x)), int32_t(std::floor(y))};
}

bool ContextDriver::isMouseButtonDown(ContextWindow& window, MouseButton button) const noexcept {
	return glfwGetMouseButton(window.m_win, static_cast<int32_t>(button)) == GLFW_PRESS;
}

bool ContextDriver::isKeyDown(ContextWindow& window, Key key) const noexcept {
	return glfwGetKey(window.m_win, static_cast<int32_t>(key)) == GLFW_PRESS;
}

ContextDriver::GlGetProcAddress ContextDriver::getGlGetProcAddressFunc() const noexcept {
	return reinterpret_cast<GlGetProcAddress>(glfwGetProcAddress);
}

void ContextDriver::terminate() noexcept {
	glfwTerminate();
}

} // namespace ngn::prv
