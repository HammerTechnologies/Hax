#pragma once

#include <cmath>
#include <cstdint>
#include "../math/mat4.h"
#include "../math/quat.h"
#include "../math/vec3.h"
#include "../real.h"

struct Viewer {
	Vec3r m_position;
	Vec3r m_euler;
	uint16_t m_viewportX;
	uint16_t m_viewportY;
	uint16_t m_viewportWidth;
	uint16_t m_viewportHeight;
	real_t m_fov;
	real_t m_rangeMin;
	real_t m_rangeMax;

	constexpr Viewer(
		const Vec3r& position,
		const Vec3r& euler,
		uint16_t viewportX,
		uint16_t viewportY,
		uint16_t viewportWidth,
		uint16_t viewportHeight,
		real_t fov = 60,
		real_t rangeMin = 1,
		real_t rangeMax = 1000) noexcept
	:	m_position{position},
		m_euler{euler},
		m_viewportX{viewportX},
		m_viewportY{viewportY},
		m_viewportWidth{viewportWidth},
		m_viewportHeight{viewportHeight},
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
