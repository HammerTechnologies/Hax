#pragma once

#include <cstdint>
#include <memory>
#include "../real.h"

struct GLFWwindow;

struct Screen {
	Screen(const std::shared_ptr<GLFWwindow>& window) noexcept;

	void enableContext() const noexcept;
	uint16_t getWidth() const noexcept;
	uint16_t getHeight() const noexcept;
	bool isOpened() const noexcept;
	void refresh() noexcept;

	constexpr real_t getDelta() const noexcept { return m_delta; }
	constexpr uint32_t getFps() const noexcept { return m_fps; }
private:
	std::shared_ptr<GLFWwindow> m_window;
	real_t m_delta;
	double m_lastTime;
	uint32_t m_fps;
	uint32_t m_fpsCounter;
	real_t m_fpsTime;
};
