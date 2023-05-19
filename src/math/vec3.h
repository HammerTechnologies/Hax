#pragma once

#include <cmath>
#include "../real.h"

template<typename T>
constexpr T deg2rad(const T& a) noexcept { return static_cast<T>(a * 0.0174532925); }

template<typename T>
constexpr T rad2deg(const T& a) noexcept { return static_cast<T>(a * 57.2957795); }

template<typename T>
struct Vec3 {
	T m_x, m_y, m_z;

	constexpr Vec3(T x = 0, T y = 0, T z = 0) noexcept
	: m_x{x}, m_y{y}, m_z{z} {}

	constexpr Vec3 operator+(const Vec3& other) const noexcept {
		return Vec3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
	}

	constexpr Vec3 operator+(const T& scalar) const noexcept {
		return Vec3(m_x + scalar, m_y + scalar, m_z + scalar);
	}

	constexpr Vec3 operator-(const Vec3& other) const noexcept {
		return Vec3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
	}

	constexpr Vec3 operator-(const T& scalar) const noexcept {
		return Vec3(m_x - scalar, m_y - scalar, m_z - scalar);
	}

	constexpr Vec3 operator*(const Vec3& other) const noexcept {
		return Vec3(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z);
	}

	constexpr Vec3 operator*(const T& scalar) const noexcept {
		return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
	}

	constexpr Vec3 operator/(const Vec3& other) const noexcept {
		return Vec3(m_x / other.m_x, m_y / other.m_y, m_z / other.m_z);
	}

	constexpr Vec3 operator/(const T& scalar) const noexcept {
		return Vec3(m_x / scalar, m_y / scalar, m_z / scalar);
	}

	constexpr T dot(const Vec3& other) const noexcept {
		return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
	}

	constexpr Vec3 cross(const Vec3& other) const noexcept {
		return Vec3(m_y*other.m_z - m_z*other.m_y, m_z*other.m_x -m_x*other.m_z, m_x*other.m_y - m_y*other.m_x);
	}

	constexpr T sqlength() const noexcept {
		return dot(*this);
	}

	constexpr T length() const noexcept {
		return std::sqrt(sqlength());
	}

	constexpr Vec3 norm() const noexcept {
		const T length = length();
		const T invLength = (length > 0) ? (1 / length) : 0;
		return *this * invLength;
	}

	constexpr Vec3 mix(const Vec3& other, const T& t) const noexcept {
		return *this + (other - *this) * t;
	}

	constexpr Vec3 deg() const noexcept {
		return Vec3(rad2deg(m_x), rad2deg(m_y), rad2deg(m_z));
	}

	constexpr Vec3 rad() const noexcept {
		return Vec3(deg2rad(m_x), deg2rad(m_y), deg2rad(m_z));
	}
};

using Vec3r = Vec3<real_t>;
