#include <cmath>
#include <GLFW/glfw3.h>
#include "input.h"

void Input::setMouseVisible(bool visible) const noexcept {
	glfwSetInputMode(m_window.get(), GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void Input::setMousePosition(int32_t x, int32_t y) const noexcept {
	glfwSetCursorPos(m_window.get(), x, y);
}

int32_t Input::getMouseX() const noexcept {
	double x;
	glfwGetCursorPos(m_window.get(), &x, nullptr);
	return static_cast<int32_t>(std::floor(x));
}

int32_t Input::getMouseY() const noexcept {
	double y;
	glfwGetCursorPos(m_window.get(), nullptr, &y);
	return static_cast<int32_t>(std::floor(y));
}

bool Input::isMouseButtonDown(MouseButton button) const noexcept {
	return glfwGetMouseButton(m_window.get(), static_cast<int32_t>(button)) == GLFW_PRESS;
}

bool Input::isKeyDown(Key key) const noexcept {
	return glfwGetKey(m_window.get(), static_cast<int32_t>(key)) == GLFW_PRESS;
}
