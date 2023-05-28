#pragma once

#include <cstdint>
#include <memory>
#include "internal/context_driver.h"
#include "key.h"
#include "mouse_button.h"

struct Input {
	Input(const ContextDriver& context, const std::shared_ptr<ContextWindow> window)
	: m_context{context}, m_window{window} {}

  void setMouseVisible(bool visible) const noexcept;
  void setMousePosition(int32_t x, int32_t y) const noexcept;
  int32_t getMouseX() const noexcept;
  int32_t getMouseY() const noexcept;
  bool isMouseButtonDown(MouseButton button) const noexcept;
  bool isKeyDown(Key key) const noexcept;
private:
	const ContextDriver& m_context;
	std::shared_ptr<ContextWindow> m_window;
};
