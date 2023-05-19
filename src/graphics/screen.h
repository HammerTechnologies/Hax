#pragma once

#include <cstdint>
#include <memory>

struct GLFWwindow;

struct Screen {
	Screen(uint16_t width, uint16_t height, bool fullscreen) noexcept;
	~Screen() noexcept;

	void enableContext() const noexcept;
	uint16_t getWidth() const noexcept;
	uint16_t getHeight() const noexcept;
	bool isOpened() const noexcept;
	void refresh() const noexcept;
private:
	static uint8_t m_initCounter;
	std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;
};
