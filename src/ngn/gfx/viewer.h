#pragma once

#include <cmath>
#include <cstdint>
#include "../mth/mat4.h"
#include "../mth/quat.h"
#include "../mth/vec2.h"
#include "../mth/vec3.h"
#include "../mth/real.h"

namespace ngn {

struct Viewer {
	constexpr Viewer(
		const Vec3r& position,
		const Vec3r& euler,
		const Vec2<uint16_t>& viewportPosition,
		const Vec2<uint16_t>& viewportSize,
		real_t fov = 60,
		real_t rangeMin = 1,
		real_t rangeMax = 1000) noexcept
	:	m_position{position},
		m_euler{euler},
		m_viewportPosition{viewportPosition},
		m_viewportSize{viewportSize},
		m_fov{fov},
		m_rangeMin{rangeMin},
		m_rangeMax{rangeMax} {}

	constexpr const Vec3r& position() const noexcept { return m_position; }
	constexpr const Vec3r& euler() const noexcept { return m_euler; }
	constexpr const Vec2<uint16_t>& viewportPosition() const noexcept { return m_viewportPosition; }
	constexpr const Vec2<uint16_t>& viewportSize() const noexcept { return m_viewportSize; }
	constexpr real_t fov() const noexcept { return m_fov; }
	constexpr real_t rangeMin() const noexcept { return m_rangeMin; }
	constexpr real_t rangeMax() const noexcept { return m_rangeMax; }
	constexpr void position(const Vec3r& position) noexcept { m_position = position; }
	constexpr void euler(const Vec3r& euler) noexcept { m_euler = euler; }
	constexpr void viewportPosition(const Vec2<uint16_t>& position) noexcept { m_viewportPosition = position; }
	constexpr void viewportSize(const Vec2<uint16_t>& size) noexcept { m_viewportSize = size; }
	constexpr void fov(real_t fov) noexcept { m_fov = fov; }
	constexpr void rangeMin(real_t min) noexcept { m_rangeMin = min; }
	constexpr void rangeMax(real_t max) noexcept { m_rangeMax = max; }

	constexpr void move(const Vec3r& amount) noexcept {
		m_position += Quatr::fromEuler(m_euler.rad()) * amount;
	}

	constexpr void lookAt(const Vec3r& position) noexcept {
		const auto dir = (position - m_position).norm();
		m_euler.x(rad2deg(std::asin(-dir.y())));
		m_euler.y(rad2deg(std::atan2(dir.x(), dir.z())));
	}

	constexpr Mat4r viewMatrix() const noexcept {
		const auto q = Quatr::fromEuler(m_euler.rad());
		return Mat4r{}
			.rotate(-q.angle(), q.axis())
			.translate(-m_position);
	}
private:
	Vec3r m_position;
	Vec3r m_euler;
	Vec2<uint16_t> m_viewportPosition;
	Vec2<uint16_t> m_viewportSize;
	real_t m_fov;
	real_t m_rangeMin;
	real_t m_rangeMax;
};

} // namespace ngn
