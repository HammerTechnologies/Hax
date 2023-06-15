#pragma once

#include <algorithm>
#include <cstdint>
#include "../math/real.h"

using color_t = uint32_t;
using colorcomp_t = uint8_t;

struct Color {
	static constexpr color_t RED = -65536;
	static constexpr color_t GREEN = -16711936;
	static constexpr color_t BLUE = -16776961;
	static constexpr color_t CYAN = -16711681;
	static constexpr color_t MAGENTA = -65281;
	static constexpr color_t YELLOW = -256;
	static constexpr color_t BLACK = -16777216;
	static constexpr color_t WHITE = -1;
	static constexpr color_t GRAY = -8355712;
	static constexpr color_t LIGHTGRAY = -4210753;
	static constexpr color_t DARKGRAY = -12566464;
	static constexpr color_t ORANGE = -23296;
	static constexpr color_t BROWN = -7650029;

	static constexpr color_t rgb(colorcomp_t r, colorcomp_t g, colorcomp_t b, colorcomp_t a = 255) noexcept {
		r = std::clamp<colorcomp_t>(r, 0, 255);
		g = std::clamp<colorcomp_t>(g, 0, 255);
		b = std::clamp<colorcomp_t>(b, 0, 255);
		a = std::clamp<colorcomp_t>(a, 0, 255);
		return (a << 24) | (r << 16) | (g << 8) | b;
	}

	static constexpr color_t rgbf(real_t r, real_t g, real_t b, real_t a = 1) noexcept {
		return rgb(
			colorcomp_t(r * 255),
			colorcomp_t(g * 255),
			colorcomp_t(b * 255),
			colorcomp_t(a * 255));
	}

	static constexpr colorcomp_t red(color_t color) noexcept {
		return (color >> 16) & 0xff;
	}

	static constexpr colorcomp_t green(color_t color) noexcept {
		return (color >> 8) & 0xff;
	}

	static constexpr colorcomp_t blue(color_t color) noexcept {
		return color & 0xff;
	}

	static constexpr colorcomp_t alpha(color_t color) noexcept {
		return (color >> 24) & 0xff;
	}

	static constexpr real_t redf(color_t color) noexcept {
		return real_t(red(color)) / 255.0f;
	}

	static constexpr real_t greenf(color_t color) noexcept {
		return real_t(green(color)) / 255.0f;
	}

	static constexpr real_t bluef(color_t color) noexcept {
		return real_t(blue(color)) / 255.0f;
	}

	static constexpr real_t alphaf(color_t color) noexcept {
		return real_t(alpha(color)) / 255.0f;
	}

	static constexpr color_t withAlpha(color_t color, colorcomp_t new_alpha) noexcept {
		return (std::clamp<colorcomp_t>(new_alpha, 0, 255) << 24) | (color & 0x00ffffff);
	}

	static constexpr color_t multiply(color_t color, real_t factor) noexcept {
		return rgbf(
			redf(color) * factor,
			greenf(color) * factor,
			bluef(color) * factor,
			alphaf(color));
	}
};
