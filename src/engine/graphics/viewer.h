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
		const Vec3r dir = (position - m_position).norm();
		m_euler.m_x = rad2deg(std::asin(-dir.m_y));
		m_euler.m_y = rad2deg(std::atan2(dir.m_x, dir.m_z));
	}

	constexpr Mat4r getViewMatrix() const noexcept {
		return Mat4r{}
			.rotate(Quatr::fromEuler(m_euler.rad()))
			.translate(-m_position);
	}
};
