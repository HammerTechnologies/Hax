#include <sstream>
#include <GLFW/glfw3.h>
#include "../logger.h"
#include "core.h"

static bool _isInit = glfwInit() == GLFW_TRUE;

Core::Core(uint16_t width, uint16_t height, bool fullscreen, const Logger& logger) noexcept
: m_logger{logger},
	m_window{
		glfwCreateWindow(width, height, "Hax", fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr),
		glfwDestroyWindow
	},
	m_screen{m_window, logger},
	m_input{m_window},
	m_graphics{reinterpret_cast<void*(*)(const char*)>(glfwGetProcAddress), logger} {
	if (!_isInit) {
		m_logger.error("Could not initialize GLFW.");
	} else {
		int32_t major, minor, rev;
		glfwGetVersion(&major, &minor, &rev);
		std::ostringstream ss;
		ss << "GLFW version " << major << "." << minor << "." << rev << ".";
		m_logger.info(ss.str());
	}
	if (!m_window) {
		m_logger.error("Could not create window.");
	}
	m_logger.info("Core services initializated.");
}

Core::~Core() noexcept {
	m_logger.info("Core services deinitializing...");
}

void Core::terminate() noexcept {
	glfwTerminate();
}
