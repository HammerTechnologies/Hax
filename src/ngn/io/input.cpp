#include "input.h"

void Input::mouseVisible(bool visible) const noexcept {
	m_context.setMouseVisible(*m_window, visible);
}

Vec2i Input::mousePosition() const noexcept {
	return m_context.getMousePosition(*m_window);
}

void Input::mousePosition(const Vec2i& position) const noexcept {
	m_context.setMousePosition(*m_window, position);
}

bool Input::isMouseButtonDown(MouseButton button) const noexcept {
	return m_context.isMouseButtonDown(*m_window, button);
}

bool Input::isKeyDown(Key key) const noexcept {
	return m_context.isKeyDown(*m_window, key);
}
