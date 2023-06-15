#pragma once

#include <cstdint>
#include "../../math/vec2.h"
#include "../../real.h"
#include "../key.h"
#include "../mouse_button.h"

struct GLFWwindow;
struct Logger;

using ContextWindow = GLFWwindow;

struct ContextDriver {
	using GlGetProcAddress = void*(*)(const char*);

	ContextDriver(const Logger& logger) noexcept;
	ContextWindow* createWindow(const Vec2<uint16_t>& size, bool fullscreen) const noexcept;
	void destroyWindow(ContextWindow& window) const noexcept;
	void enableWindowContext(ContextWindow& window) const noexcept;
	Vec2<uint16_t> getWindowSize(ContextWindow& window) const noexcept;
	bool isWindowOpened(ContextWindow& window) const noexcept;
	void refreshWindow(ContextWindow& window) const noexcept;

	real_t getTime() const noexcept;

  void setMouseVisible(ContextWindow& window, bool visible) const noexcept;
  void setMousePosition(ContextWindow& window, const Vec2i& position) const noexcept;
  Vec2i getMousePosition(ContextWindow& window) const noexcept;
  bool isMouseButtonDown(ContextWindow& window, MouseButton button) const noexcept;
  bool isKeyDown(ContextWindow& window, Key key) const noexcept;

	GlGetProcAddress getGlGetProcAddressFunc() const noexcept;

	static void terminate() noexcept;
private:
	const Logger& m_logger;
};
