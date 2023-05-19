#pragma once

#include <cmath>
#include "../real.h"
#include "vec3.h"

template <typename T>
struct Quat {
	T m_w, m_x, m_y, m_z;

	constexpr Quat(const T& w = 1, const T& x = 0, const T& y = 0, const T& z = 0) noexcept
	: m_w(w), m_x(x), m_y(y), m_z(z) {}

	constexpr static Quat fromAxis(const T& angle, const Vec3<T>& axis) noexcept {
		const T& halfAngle = angle / 2;
		const Vec3<T> v{axis.norm() * std::sin(halfAngle)};
		return Quat{std::cos(halfAngle), v.m_x, v.m_y, v.m_z};
	}

	constexpr static Quat fromEuler(const Vec3<T>& euler) noexcept {
		const T halfx = euler.m_x / 2;
		const T halfy = euler.m_y / 2;
		const T halfz = euler.m_z / 2;
		const T sinx = std::sin(halfx);
		const T siny = std::sin(halfy);
		const T sinz = std::sin(halfz);
		const T cosx = std::cos(halfx);
		const T cosy = std::cos(halfy);
		const T cosz = std::cos(halfz);
		return Quat{
			cosx * cosy * cosz + sinx * siny * sinz,
			sinx * cosy * cosz - cosx * siny * sinz,
			cosx * siny * cosz + sinx * cosy * sinz,
			cosx * cosy * sinz - sinx * siny * cosz
		};
	}

	constexpr Quat operator+(const Quat& other) const noexcept {
		return Quat{m_w + other.m_w, m_x + other.m_x, m_y + other.m_y, m_z + other.m_z};
	}

	constexpr Quat operator*(const Quat& other) const noexcept {
		return Quat{
			m_w*other.m_w - m_x*other.m_x - m_y*other.m_y - m_z*other.m_z,
			m_w*other.m_x + m_x*other.m_w + m_y*other.m_z - m_z*other.m_y,
			m_w*other.m_y + m_y*other.m_w + m_z*other.m_x - m_x*other.m_z,
			m_w*other.m_z + m_z*other.m_w + m_x*other.m_y - m_y*other.m_x
		};
	}

	constexpr Vec3<T> operator*(const Vec3<T>& v) const noexcept {
		const Quat q{*this * Quat{0, v.m_x, v.m_y, v.m_z} * conj()};
		return Vec3<T>{q.m_x, q.m_y, q.m_z};
	}

	constexpr Quat operator*(const T& scalar) const noexcept {
		return Quat{m_w * scalar, m_x * scalar, m_y * scalar, m_z * scalar};
	}

	constexpr Quat operator/(const T& scalar) const noexcept {
		return Quat{m_w / scalar, m_x / scalar, m_y / scalar, m_z / scalar};
	}

	constexpr Quat norm() const noexcept {
		const Quat result{*this};
		const T mag2 = m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w;
		if (mag2 > static_cast<T>(0.00001) && std::abs(mag2 - static_cast<T>(1.0)) > static_cast<T>(0.00001)) {
			const T invmag = static_cast<T>(1) / std::sqrt(mag2);
			result.m_w *= invmag;
			result.m_x *= invmag;
			result.m_y *= invmag;
			result.m_z *= invmag;
		}
		return result;
	}

	constexpr Quat conj() const noexcept {
		return Quat{m_w, -m_x, -m_y, -m_z};
	}

	constexpr Quat lerp(const Quat& other, const T& t) const noexcept {
		return (*this * (1-t) + other * t).norm();
	}

	constexpr Quat slerp(const Quat& other, const T& t) const noexcept {
		const T dot = this->dot(other);
		const Quat q{(dot < 0) ? (other * -1) : other};
		const T absdot = std::abs(dot);
		if (absdot < 0.95f) {
			const T angle = std::acos(absdot);
			return Quat{*this * std::sin(angle * (1-t)) + q * std::sin(angle*t) / std::sin(angle)};
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
		const T scale = std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
		const T invscale = (scale > 0) ? (static_cast<T>(1) / scale) : 0;
		return Vec3<T>{m_x * invscale, m_y * invscale, m_z * invscale};
	}

	constexpr Vec3<T> euler() const noexcept {
		return Vec3{
			std::atan2(2 * (m_y*m_z + m_w*m_x), m_w*m_w - m_x*m_x - m_y*m_y + m_z*m_z),
			std::asin(-2 * (m_x*m_z - m_w*m_y)),
			std::atan2(2 * (m_x*m_y + m_w*m_z), m_w*m_w + m_x*m_x - m_y*m_y - m_z*m_z)
		};
	}
};

using Quatr = Quat<real_t>;
