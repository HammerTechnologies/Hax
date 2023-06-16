#pragma once

#include <cstdint>
#include <memory>
#include "../_prv/context_driver.h"
#include "../mth/vec2.h"
#include "key.h"
#include "mouse_button.h"

namespace ngn {

struct Input {
	Input(const prv::ContextDriver& context, const std::shared_ptr<prv::ContextWindow>& window) noexcept
	: m_context{context}, m_window{window} {}

  void mouseVisible(bool visible) const noexcept;
	Vec2i mousePosition() const noexcept;
  void mousePosition(const Vec2i& position) const noexcept;
  bool isMouseButtonDown(MouseButton button) const noexcept;
  bool isKeyDown(Key key) const noexcept;
private:
	const prv::ContextDriver& m_context;
	std::shared_ptr<prv::ContextWindow> m_window;
};

} // namespace ngn
