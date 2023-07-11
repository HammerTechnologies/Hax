#pragma once

#include "../ngn/mth/quat.h"
#include "../ngn/mth/vec3.h"

struct Transform {
	ngn::Vec3r position {};
	ngn::real_t rotation {};
	ngn::Vec3r scale {1, 1, 1};

	constexpr void move(const ngn::Vec3r& amount) noexcept {
		position += ngn::Quatr::fromEuler(ngn::Vec3r {0, rotation, 0}.rad()) * amount;
	}
};
