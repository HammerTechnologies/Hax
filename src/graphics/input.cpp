#include "input.h"

void Input::setMouseVisible(bool visible) const noexcept {
	m_context.setMouseVisible(*m_window, visible);
}

void Input::setMousePosition(int32_t x, int32_t y) const noexcept {
	m_context.setMousePosition(*m_window, x, y);
}

int32_t Input::getMouseX() const noexcept {
	return m_context.getMouseX(*m_window);
}

int32_t Input::getMouseY() const noexcept {
	return m_context.getMouseY(*m_window);
}

bool Input::isMouseButtonDown(MouseButton button) const noexcept {
	return m_context.isMouseButtonDown(*m_window, button);
}

bool Input::isKeyDown(Key key) const noexcept {
	return m_context.isKeyDown(*m_window, key);
}
