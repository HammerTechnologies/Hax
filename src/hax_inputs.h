#pragma once

#include "ngn/io/input.h"
#include "ngn/mth/real.h"

struct HaxInputs {
	ngn::real_t forward;
	ngn::real_t right;

	void update(const ngn::Input& input) noexcept {
		forward = 0;
		right = 0;
		if (input.isKeyDown(ngn::Key::UP)) { forward += 1; }
		if (input.isKeyDown(ngn::Key::DOWN)) { forward -= 1; }
		if (input.isKeyDown(ngn::Key::LEFT)) { right -= 1; }
		if (input.isKeyDown(ngn::Key::RIGHT)) { right += 1; }
	}
};
