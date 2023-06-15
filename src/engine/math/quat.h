#pragma once

#include <cmath>
#include "../real.h"
#include "vec3.h"

template <typename T>
struct Quat {
	constexpr Quat(const T& w = 1, const T& x = 0, const T& y = 0, const T& z = 0) noexcept
	: m_w(w), m_x(x), m_y(y), m_z(z) {}

	constexpr static Quat fromAxis(const T& angle, const Vec3<T>& axis) noexcept {
		const auto halfAngle = angle / 2;
		const auto v = axis.norm() * std::sin(halfAngle);
		return {std::cos(halfAngle), v.x(), v.y(), v.z()};
	}

	constexpr static Quat fromEuler(const Vec3<T>& euler) noexcept {
		const auto halfx = euler.x() / 2;
		const auto halfy = euler.y() / 2;
		const auto halfz = euler.z() / 2;
		const auto sinx = std::sin(halfx);
		const auto siny = std::sin(halfy);
		const auto sinz = std::sin(halfz);
		const auto cosx = std::cos(halfx);
		const auto cosy = std::cos(halfy);
		const auto cosz = std::cos(halfz);
		return {
			cosx * cosy * cosz + sinx * siny * sinz,
			sinx * cosy * cosz - cosx * siny * sinz,
			cosx * siny * cosz + sinx * cosy * sinz,
			cosx * cosy * sinz - sinx * siny * cosz
		};
	}

	constexpr Quat operator+(const Quat& other) const noexcept {
		return {m_w + other.m_w, m_x + other.m_x, m_y + other.m_y, m_z + other.m_z};
	}

	constexpr Quat operator*(const Quat& other) const noexcept {
		return {
			m_w*other.m_w - m_x*other.m_x - m_y*other.m_y - m_z*other.m_z,
			m_w*other.m_x + m_x*other.m_w + m_y*other.m_z - m_z*other.m_y,
			m_w*other.m_y + m_y*other.m_w + m_z*other.m_x - m_x*other.m_z,
			m_w*other.m_z + m_z*other.m_w + m_x*other.m_y - m_y*other.m_x
		};
	}

	constexpr Vec3<T> operator*(const Vec3<T>& v) const noexcept {
		const auto q = *this * Quat{0, v.x(), v.y(), v.z()} * conj();
		return {q.m_x, q.m_y, q.m_z};
	}

	constexpr Quat operator*(const T& scalar) const noexcept {
		return {m_w * scalar, m_x * scalar, m_y * scalar, m_z * scalar};
	}

	constexpr Quat operator/(const T& scalar) const noexcept {
		return {m_w / scalar, m_x / scalar, m_y / scalar, m_z / scalar};
	}

	constexpr const T& w() const noexcept { return m_w; }
	constexpr const T& x() const noexcept { return m_x; }
	constexpr const T& y() const noexcept { return m_y; }
	constexpr const T& z() const noexcept { return m_z; }
	constexpr T& w() noexcept { return m_w; }
	constexpr T& x() noexcept { return m_x; }
	constexpr T& y() noexcept { return m_y; }
	constexpr T& z() noexcept { return m_z; }

	constexpr const T* data() const noexcept { return &m_w; }
	constexpr T* data() noexcept { return &m_w; }

	constexpr Quat norm() const noexcept {
		const auto result = *this;
		const auto mag2 = m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w;
		if (mag2 > T{0.00001} && std::abs(mag2 - T{1.0}) > T{0.00001}) {
			const auto invmag = T{1} / std::sqrt(mag2);
			result.m_w *= invmag;
			result.m_x *= invmag;
			result.m_y *= invmag;
			result.m_z *= invmag;
		}
		return result;
	}

	constexpr Quat conj() const noexcept {
		return {m_w, -m_x, -m_y, -m_z};
	}

	constexpr Quat lerp(const Quat& other, const T& t) const noexcept {
		return (*this * (1-t) + other * t).norm();
	}

	constexpr Quat slerp(const Quat& other, const T& t) const noexcept {
		const auto dot = this->dot(other);
		const auto q = (dot < 0) ? (other * -1) : other;
		const T absdot = std::abs(dot);
		if (absdot < 0.95f) {
			const auto angle = std::acos(absdot);
			return *this * std::sin(angle * (1-t)) + q * std::sin(angle*t) / std::sin(angle);
		} else {
			return this->lerp(q, t);
		}
	}

	constexpr T dot(const Quat& other) const noexcept {
		return m_w*other.m_w + m_x*other.m_x + m_y*other.m_y + m_z*other.m_z;
	}

	constexpr T angle() const noexcept {
		return std::acos(m_w) * 2;
	}

	constexpr Vec3<T> axis() const noexcept {
		const auto scale = std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
		const auto invscale = (scale > 0) ? (T{1} / scale) : 0;
		return {m_x * invscale, m_y * invscale, m_z * invscale};
	}

	constexpr Vec3<T> euler() const noexcept {
		return {
			std::atan2(2 * (m_y*m_z + m_w*m_x), m_w*m_w - m_x*m_x - m_y*m_y + m_z*m_z),
			std::asin(-2 * (m_x*m_z - m_w*m_y)),
			std::atan2(2 * (m_x*m_y + m_w*m_z), m_w*m_w + m_x*m_x - m_y*m_y - m_z*m_z)
		};
	}
private:
	T m_w, m_x, m_y, m_z;
};

using Quatr = Quat<real_t>;
