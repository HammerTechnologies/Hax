#pragma once

#include <cstdint>
#include <memory>
#include "../gfx/_internal/context_driver.h"
#include "../mth/vec2.h"
#include "key.h"
#include "mouse_button.h"

struct Input {
	Input(const ContextDriver& context, const std::shared_ptr<ContextWindow> window)
	: m_context{context}, m_window{window} {}

  void mouseVisible(bool visible) const noexcept;
	Vec2i mousePosition() const noexcept;
  void mousePosition(const Vec2i& position) const noexcept;
  bool isMouseButtonDown(MouseButton button) const noexcept;
  bool isKeyDown(Key key) const noexcept;
private:
	const ContextDriver& m_context;
	std::shared_ptr<ContextWindow> m_window;
};
