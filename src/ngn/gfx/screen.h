#pragma once

#include <cstdint>
#include <memory>
#include "../mth/vec2.h"
#include "../mth/real.h"
#include "../_prv/context_driver.h"

namespace ngn {

struct Logger;

struct Screen {
	Screen(
		const prv::ContextDriver& context,
		const std::shared_ptr<prv::ContextWindow>& window,
		const Logger& logger) noexcept;
	~Screen() noexcept;

	void enableContext() const noexcept;
	Vec2<uint16_t> size() const noexcept;
	bool isOpened() const noexcept;
	void refresh() noexcept;

	constexpr real_t delta() const noexcept { return m_delta; }
	constexpr uint32_t fps() const noexcept { return m_fps; }
private:
	const prv::ContextDriver& m_context;
	const Logger& m_logger;
	std::shared_ptr<prv::ContextWindow> m_window;
	real_t m_delta;
	real_t m_lastTime;
	uint32_t m_fps;
	uint32_t m_fpsCounter;
	real_t m_fpsTime;
};

} // namespace ngn
