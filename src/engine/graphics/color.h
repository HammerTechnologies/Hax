#pragma once

#include <algorithm>
#include <cstdint>
#include "../real.h"

struct Color {
	static constexpr uint32_t RED = -65536;
	static constexpr uint32_t GREEN = -16711936;
	static constexpr uint32_t BLUE = -16776961;
	static constexpr uint32_t CYAN = -16711681;
	static constexpr uint32_t MAGENTA = -65281;
	static constexpr uint32_t YELLOW = -256;
	static constexpr uint32_t BLACK = -16777216;
	static constexpr uint32_t WHITE = -1;
	static constexpr uint32_t GRAY = -8355712;
	static constexpr uint32_t LIGHTGRAY = -4210753;
	static constexpr uint32_t DARKGRAY = -12566464;
	static constexpr uint32_t ORANGE = -23296;
	static constexpr uint32_t BROWN = -7650029;

	static constexpr uint32_t rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept {
		r = std::clamp<uint8_t>(r, 0, 255);
		g = std::clamp<uint8_t>(g, 0, 255);
		b = std::clamp<uint8_t>(b, 0, 255);
		a = std::clamp<uint8_t>(a, 0, 255);
		return (a << 24) | (r << 16) | (g << 8) | b;
	}

	static constexpr uint32_t rgbf(real_t r, real_t g, real_t b, real_t a = 1) noexcept {
		return rgb(
			static_cast<uint8_t>(r * 255),
			static_cast<uint8_t>(g * 255),
			static_cast<uint8_t>(b * 255),
			static_cast<uint8_t>(a * 255));
	}

	static constexpr uint8_t red(uint32_t color) noexcept {
		return (color >> 16) & 0xff;
	}

	static constexpr uint8_t green(uint32_t color) noexcept {
		return (color >> 8) & 0xff;
	}

	static constexpr uint8_t blue(uint32_t color) noexcept {
		return color & 0xff;
	}

	static constexpr uint8_t alpha(uint32_t color) noexcept {
		return (color >> 24) & 0xff;
	}

	static constexpr real_t redf(uint32_t color) noexcept {
		return static_cast<real_t>(red(color)) / 255.0f;
	}

	static constexpr real_t greenf(uint32_t color) noexcept {
		return static_cast<real_t>(green(color)) / 255.0f;
	}

	static constexpr real_t bluef(uint32_t color) noexcept {
		return static_cast<real_t>(blue(color)) / 255.0f;
	}

	static constexpr real_t alphaf(uint32_t color) noexcept {
		return static_cast<real_t>(alpha(color)) / 255.0f;
	}

	static constexpr uint32_t withAlpha(uint32_t color, uint8_t new_alpha) noexcept {
		return (std::clamp<uint8_t>(new_alpha, 0, 255) << 24) | (color & 0x00ffffff);
	}

	static constexpr uint32_t multiply(uint32_t color, real_t factor) noexcept {
		return rgbf(redf(color) * factor, greenf(color) * factor, bluef(color) * factor, alphaf(color));
	}
};
