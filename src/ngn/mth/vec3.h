#pragma once

#include <cmath>
#include "../mth/real.h"
#include "vec2.h"

namespace ngn {

template<typename T>
constexpr T deg2rad(T a) noexcept { return T(a * 0.0174532925); }

template<typename T>
constexpr T rad2deg(T a) noexcept { return T(a * 57.2957795); }

template<typename T>
struct Vec3 {
	constexpr Vec3(T x = 0, T y = 0, T z = 0) noexcept
	: m_x{x}, m_y{y}, m_z{z} {}

	constexpr Vec3(const Vec2<T>& v, T z = 0) noexcept
	: m_x{v.x()}, m_y{v.y()}, m_z{z} {}

	constexpr bool operator==(const Vec3& other) const noexcept {
		return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
	}

	constexpr bool operator!=(const Vec3& other) const noexcept {
		return !(*this == other);
	}

	constexpr Vec3 operator+(const Vec3& other) const noexcept {
		return {m_x + other.m_x, m_y + other.m_y, m_z + other.m_z};
	}

	constexpr Vec3 operator+(T scalar) const noexcept {
		return {m_x + scalar, m_y + scalar, m_z + scalar};
	}

	constexpr Vec3& operator+=(const Vec3& other) noexcept {
		m_x += other.m_x;
		m_y += other.m_y;
		m_z += other.m_z;
		return *this;
	}

	constexpr Vec3& operator+=(T scalar) noexcept {
		m_x += scalar;
		m_y += scalar;
		m_z += scalar;
		return *this;
	}

	constexpr Vec3 operator-(const Vec3& other) const noexcept {
		return {m_x - other.m_x, m_y - other.m_y, m_z - other.m_z};
	}

	constexpr Vec3 operator-(T scalar) const noexcept {
		return {m_x - scalar, m_y - scalar, m_z - scalar};
	}

	constexpr Vec3 operator-() const noexcept {
		return {-m_x, -m_y, -m_z};
	}

	constexpr Vec3& operator-=(const Vec3& other) noexcept {
		m_x -= other.m_x;
		m_y -= other.m_y;
		m_z -= other.m_z;
		return *this;
	}

	constexpr Vec3& operator-=(T scalar) noexcept {
		m_x -= scalar;
		m_y -= scalar;
		m_z -= scalar;
		return *this;
	}

	constexpr Vec3 operator*(const Vec3& other) const noexcept {
		return {m_x * other.m_x, m_y * other.m_y, m_z * other.m_z};
	}

	constexpr Vec3 operator*(T scalar) const noexcept {
		return {m_x * scalar, m_y * scalar, m_z * scalar};
	}

	constexpr Vec3& operator*=(const Vec3& other) noexcept {
		m_x *= other.m_x;
		m_y *= other.m_y;
		m_z *= other.m_z;
		return *this;
	}

	constexpr Vec3& operator*=(T scalar) noexcept {
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		return *this;
	}

	constexpr Vec3 operator/(const Vec3& other) const noexcept {
		return {m_x / other.m_x, m_y / other.m_y, m_z / other.m_z};
	}

	constexpr Vec3 operator/(T scalar) const noexcept {
		return {m_x / scalar, m_y / scalar, m_z / scalar};
	}

	constexpr Vec3& operator/=(const Vec3& other) noexcept {
		m_x /= other.m_x;
		m_y /= other.m_y;
		m_z /= other.m_z;
		return *this;
	}

	constexpr Vec3& operator/=(T scalar) noexcept {
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		return *this;
	}

	constexpr T x() const noexcept { return m_x; }
	constexpr T y() const noexcept { return m_y; }
	constexpr T z() const noexcept { return m_z; }
	constexpr void x(T x) noexcept { m_x = x; }
	constexpr void y(T y) noexcept { m_y = y; }
	constexpr void z(T z) noexcept { m_z = z; }

	constexpr const T* data() const noexcept { return &m_x; }
	constexpr T* data() noexcept { return &m_x; }

	constexpr T dot(const Vec3& other) const noexcept {
		return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
	}

	constexpr Vec3 cross(const Vec3& other) const noexcept {
		return {
			m_y*other.m_z - m_z*other.m_y,
			m_z*other.m_x -m_x*other.m_z,
			m_x*other.m_y - m_y*other.m_x};
	}

	constexpr T sqlength() const noexcept {
		return dot(*this);
	}

	constexpr T length() const noexcept {
		return std::sqrt(sqlength());
	}

	constexpr Vec3 norm() const noexcept {
		const auto len = length();
		const auto invLen = (len > 0) ? (1 / len) : 0;
		return *this * invLen;
	}

	constexpr Vec3 mix(const Vec3& other, T t) const noexcept {
		return *this + (other - *this) * t;
	}

	constexpr Vec3 deg() const noexcept {
		return {rad2deg(m_x), rad2deg(m_y), rad2deg(m_z)};
	}

	constexpr Vec3 rad() const noexcept {
		return {deg2rad(m_x), deg2rad(m_y), deg2rad(m_z)};
	}
private:
	T m_x, m_y, m_z;
};

using Vec3r = Vec3<real_t>;

} // namespace ngn
