#pragma once

#include <cmath>
#include <cstdint>
#include "../math/mat4.h"
#include "../math/quat.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../real.h"

struct Viewer {
	Vec3r m_position;
	Vec3r m_euler;
	Vec2<uint16_t> m_viewportPosition;
	Vec2<uint16_t> m_viewportSize;
	real_t m_fov;
	real_t m_rangeMin;
	real_t m_rangeMax;

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

	constexpr void move(const Vec3r& amount) noexcept {
		m_position += Quatr::fromEuler(m_euler.rad()) * amount;
	}

	constexpr void lookAt(const Vec3r& position) noexcept {
		const auto dir = (position - m_position).norm();
		m_euler.x() = rad2deg(std::asin(-dir.y()));
		m_euler.y() = rad2deg(std::atan2(dir.x(), dir.z()));
	}

	constexpr Mat4r getViewMatrix() const noexcept {
		const auto q = Quatr::fromEuler(m_euler.rad());
		return Mat4r{}
			.rotate(-q.angle(), q.axis())
			.translate(-m_position);
	}
};
