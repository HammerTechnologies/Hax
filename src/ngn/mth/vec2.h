#pragma once

#include <cmath>
#include "../mth/real.h"

namespace ngn {

template<typename T>
struct Vec2 {
	constexpr Vec2(T x = 0, T y = 0) noexcept
	: m_x{x}, m_y{y} {}

	constexpr bool operator==(const Vec2& other) const noexcept {
		return m_x == other.m_x && m_y == other.m_y;
	}

	constexpr bool operator!=(const Vec2& other) const noexcept {
		return !(*this == other);
	}

	constexpr Vec2 operator+(const Vec2& other) const noexcept {
		return {m_x + other.m_x, m_y + other.m_y};
	}

	constexpr Vec2 operator+(T scalar) const noexcept {
		return {m_x + scalar, m_y + scalar};
	}

	constexpr Vec2& operator+=(const Vec2& other) noexcept {
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}

	constexpr Vec2& operator+=(T scalar) noexcept {
		m_x += scalar;
		m_y += scalar;
		return *this;
	}

	constexpr Vec2 operator-(const Vec2& other) const noexcept {
		return {m_x - other.m_x, m_y - other.m_y};
	}

	constexpr Vec2 operator-(T scalar) const noexcept {
		return {m_x - scalar, m_y - scalar};
	}

	constexpr Vec2 operator-() const noexcept {
		return {-m_x, -m_y};
	}

	constexpr Vec2& operator-=(const Vec2& other) noexcept {
		m_x -= other.m_x;
		m_y -= other.m_y;
		return *this;
	}

	constexpr Vec2& operator-=(T scalar) noexcept {
		m_x -= scalar;
		m_y -= scalar;
		return *this;
	}

	constexpr Vec2 operator*(const Vec2& other) const noexcept {
		return {m_x * other.m_x, m_y * other.m_y};
	}

	constexpr Vec2 operator*(T scalar) const noexcept {
		return {m_x * scalar, m_y * scalar};
	}

	constexpr Vec2& operator*=(const Vec2& other) noexcept {
		m_x *= other.m_x;
		m_y *= other.m_y;
		return *this;
	}

	constexpr Vec2& operator*=(T scalar) noexcept {
		m_x *= scalar;
		m_y *= scalar;
		return *this;
	}

	constexpr Vec2 operator/(const Vec2& other) const noexcept {
		return {m_x / other.m_x, m_y / other.m_y};
	}

	constexpr Vec2 operator/(T scalar) const noexcept {
		return {m_x / scalar, m_y / scalar};
	}

	constexpr Vec2& operator/=(const Vec2& other) noexcept {
		m_x /= other.m_x;
		m_y /= other.m_y;
		return *this;
	}

	constexpr Vec2& operator/=(T scalar) noexcept {
		m_x /= scalar;
		m_y /= scalar;
		return *this;
	}

	constexpr T x() const noexcept { return m_x; }
	constexpr T y() const noexcept { return m_y; }
	constexpr void x(T x) noexcept { m_x = x; }
	constexpr void y(T y) noexcept { m_y = y; }

	constexpr const T* data() const noexcept { return &m_x; }
	constexpr T* data() noexcept { return &m_x; }

	constexpr T dot(const Vec2& other) const noexcept {
		return m_x * other.m_x + m_y * other.m_y;
	}

	constexpr T sqlength() const noexcept {
		return dot(*this);
	}

	constexpr T length() const noexcept {
		return std::sqrt(sqlength());
	}

	constexpr Vec2 norm() const noexcept {
		const auto len = length();
		const auto invLen = (len > 0) ? (1 / len) : 0;
		return *this * invLen;
	}

	constexpr Vec2 mix(const Vec2& other, T t) const noexcept {
		return *this + (other - *this) * t;
	}
private:
	T m_x, m_y;
};

using Vec2i = Vec2<int32_t>;
using Vec2r = Vec2<real_t>;

} // namespace ngn
