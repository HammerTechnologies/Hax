#pragma once

#include <cstdint>
#include <memory>
#include "../io/key.h"
#include "../io/mouse_button.h"
#include "../mth/vec2.h"
#include "../mth/real.h"

struct GLFWwindow;

namespace ngn {

struct Logger;

namespace prv {

struct ContextWindow {
	ContextWindow(GLFWwindow* win) : m_win {win} {}
	ContextWindow(ContextWindow&& other) : m_win {other.m_win} { other.m_win = nullptr; }
	~ContextWindow();
private:
	GLFWwindow* m_win;
	friend struct ContextDriver;
};

struct ContextDriver {
	using GlGetProcAddress = void*(*)(const char*);

	ContextDriver(const Logger& logger) noexcept;
	std::unique_ptr<ContextWindow> createWindow(const Vec2<uint16_t>& size, bool fullscreen) const noexcept;
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

} // namespace prv

} // namespace ngn
