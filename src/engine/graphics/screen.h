#pragma once

#include <cstdint>
#include <memory>
#include "../math/vec2.h"
#include "../math/real.h"
#include "internal/context_driver.h"

struct Logger;

struct Screen {
	Screen(const ContextDriver& context, const std::shared_ptr<ContextWindow>& window, const Logger& logger) noexcept;
	~Screen() noexcept;

	void enableContext() const noexcept;
	Vec2<uint16_t> getSize() const noexcept;
	bool isOpened() const noexcept;
	void refresh() noexcept;

	constexpr real_t getDelta() const noexcept { return m_delta; }
	constexpr uint32_t getFps() const noexcept { return m_fps; }
private:
	const ContextDriver& m_context;
	const Logger& m_logger;
	std::shared_ptr<ContextWindow> m_window;
	real_t m_delta;
	real_t m_lastTime;
	uint32_t m_fps;
	uint32_t m_fpsCounter;
	real_t m_fpsTime;
};
