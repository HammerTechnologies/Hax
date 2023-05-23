#include <GLFW/glfw3.h>
#include "core.h"

static bool _isInit = glfwInit() == GLFW_TRUE;

Core::Core(uint16_t width, uint16_t height, bool fullscreen) noexcept
: m_window{
		glfwCreateWindow(width, height, "Hax", fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr),
		glfwDestroyWindow
	},
	m_screen{m_window},
	m_input{m_window},
	m_graphics{reinterpret_cast<void*(*)(const char*)>(glfwGetProcAddress)} {
	atexit(glfwTerminate);
}
