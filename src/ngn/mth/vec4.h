#pragma once

#include <cmath>
#include "../mth/real.h"
#include "vec3.h"

namespace ngn {

template<typename T>
struct Vec4 {
	constexpr Vec4(T x = 0, T y = 0, T z = 0, T w = 0) noexcept
	: m_x{x}, m_y{y}, m_z{z}, m_w{w} {}

	constexpr Vec4(const Vec3<T>& v, T w = 0) noexcept
	: m_x{v.x()}, m_y{v.y()}, m_z{v.z()}, m_w{w} {}

	constexpr bool operator==(const Vec4& other) const noexcept {
		return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z && m_w == other.m_w;
	}

	constexpr bool operator!=(const Vec4& other) const noexcept {
		return !(*this == other);
	}

	constexpr Vec4 operator+(const Vec4& other) const noexcept {
		return {m_x + other.m_x, m_y + other.m_y, m_z + other.m_z, m_w + other.m_w};
	}

	constexpr Vec4 operator+(T scalar) const noexcept {
		return {m_x + scalar, m_y + scalar, m_z + scalar, m_w + scalar};
	}

	constexpr Vec4& operator+=(const Vec4& other) noexcept {
		m_x += other.m_x;
		m_y += other.m_y;
		m_z += other.m_z;
		m_w += other.m_w;
		return *this;
	}

	constexpr Vec4& operator+=(T scalar) noexcept {
		m_x += scalar;
		m_y += scalar;
		m_z += scalar;
		m_w += scalar;
		return *this;
	}

	constexpr Vec4 operator-(const Vec4& other) const noexcept {
		return {m_x - other.m_x, m_y - other.m_y, m_z - other.m_z, m_w - other.m_w};
	}

	constexpr Vec4 operator-(T scalar) const noexcept {
		return {m_x - scalar, m_y - scalar, m_z - scalar, m_w - scalar};
	}

	constexpr Vec4 operator-() const noexcept {
		return {-m_x, -m_y, -m_z, -m_w};
	}

	constexpr Vec4& operator-=(const Vec4& other) noexcept {
		m_x -= other.m_x;
		m_y -= other.m_y;
		m_z -= other.m_z;
		m_w -= other.m_w;
		return *this;
	}

	constexpr Vec4& operator-=(T scalar) noexcept {
		m_x -= scalar;
		m_y -= scalar;
		m_z -= scalar;
		m_w -= scalar;
		return *this;
	}

	constexpr Vec4 operator*(const Vec4& other) const noexcept {
		return {m_x * other.m_x, m_y * other.m_y, m_z * other.m_z, m_w * other.m_w};
	}

	constexpr Vec4 operator*(T scalar) const noexcept {
		return {m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar};
	}

	constexpr Vec4& operator*=(const Vec4& other) noexcept {
		m_x *= other.m_x;
		m_y *= other.m_y;
		m_z *= other.m_z;
		m_w *= other.m_w;
		return *this;
	}

	constexpr Vec4& operator*=(T scalar) noexcept {
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		m_w *= scalar;
		return *this;
	}

	constexpr Vec4 operator/(const Vec4& other) const noexcept {
		return {m_x / other.m_x, m_y / other.m_y, m_z / other.m_z, m_w / other.m_w};
	}

	constexpr Vec4 operator/(T scalar) const noexcept {
		return {m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar};
	}

	constexpr Vec4& operator/=(const Vec4& other) noexcept {
		m_x /= other.m_x;
		m_y /= other.m_y;
		m_z /= other.m_z;
		m_w /= other.m_w;
		return *this;
	}

	constexpr Vec4& operator/=(T scalar) noexcept {
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		m_w /= scalar;
		return *this;
	}

	constexpr T x() const noexcept { return m_x; }
	constexpr T y() const noexcept { return m_y; }
	constexpr T z() const noexcept { return m_z; }
	constexpr T w() const noexcept { return m_w; }
	constexpr void x(T x) noexcept { m_x = x; }
	constexpr void y(T y) noexcept { m_y = y; }
	constexpr void z(T z) noexcept { m_z = z; }
	constexpr void w(T w) noexcept { m_w = w; }

	constexpr const T* data() const noexcept { return &m_x; }
	constexpr T* data() noexcept { return &m_x; }

	constexpr T dot(const Vec4& other) const noexcept {
		return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z + m_w * other.m_w;
	}

	constexpr T sqlength() const noexcept {
		return dot(*this);
	}

	constexpr T length() const noexcept {
		return std::sqrt(sqlength());
	}

	constexpr Vec4 norm() const noexcept {
		const auto len = length();
		const auto invLen = (len > 0) ? (1 / len) : 0;
		return *this * invLen;
	}

	constexpr Vec4 mix(const Vec4& other, T t) const noexcept {
		return *this + (other - *this) * t;
	}
private:
	T m_x, m_y, m_z, m_w;
};

using Vec4r = Vec4<real_t>;

} // namespace ngn
