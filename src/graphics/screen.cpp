#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "screen.h"

uint8_t Screen::m_initCounter = 0;

Screen::Screen(uint16_t width, uint16_t height, bool fullscreen) noexcept
: m_window(nullptr, glfwDestroyWindow) {
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

void Screen::refresh() const noexcept {
	glfwSwapBuffers(m_window.get());
	glfwPollEvents();
}
