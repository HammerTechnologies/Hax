#include "input.h"

void Input::setMouseVisible(bool visible) const noexcept {
	m_context.setMouseVisible(*m_window, visible);
}

void Input::setMousePosition(const Vec2i& position) const noexcept {
	m_context.setMousePosition(*m_window, position);
}

Vec2i Input::getMousePosition() const noexcept {
	return m_context.getMousePosition(*m_window);
}

bool Input::isMouseButtonDown(MouseButton button) const noexcept {
	return m_context.isMouseButtonDown(*m_window, button);
}

bool Input::isKeyDown(Key key) const noexcept {
	return m_context.isKeyDown(*m_window, key);
}
