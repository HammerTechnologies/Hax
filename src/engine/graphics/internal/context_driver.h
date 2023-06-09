#pragma once

#include <cstdint>
#include "../../real.h"
#include "../key.h"
#include "../mouse_button.h"

struct GLFWwindow;
struct Logger;

using ContextWindow = GLFWwindow;

struct ContextDriver {
	using GlGetProcAddress = void*(*)(const char*);

	ContextDriver(const Logger& logger) noexcept;
	ContextWindow* createWindow(uint16_t width, uint16_t height, bool fullscreen) const noexcept;
	void destroyWindow(ContextWindow& window) const noexcept;
	void enableWindowContext(ContextWindow& window) const noexcept;
	uint16_t getWindowWidth(ContextWindow& window) const noexcept;
	uint16_t getWindowHeight(ContextWindow& window) const noexcept;
	bool isWindowOpened(ContextWindow& window) const noexcept;
	void refreshwindow(ContextWindow& window) const noexcept;

	real_t getTime() const noexcept;

  void setMouseVisible(ContextWindow& window, bool visible) const noexcept;
  void setMousePosition(ContextWindow& window, int32_t x, int32_t y) const noexcept;
  int32_t getMouseX(ContextWindow& window) const noexcept;
  int32_t getMouseY(ContextWindow& window) const noexcept;
  bool isMouseButtonDown(ContextWindow& window, MouseButton button) const noexcept;
  bool isKeyDown(ContextWindow& window, Key key) const noexcept;

	GlGetProcAddress getGlGetProcAddressFunc() const noexcept;

	static void terminate() noexcept;
private:
	const Logger& m_logger;
};
