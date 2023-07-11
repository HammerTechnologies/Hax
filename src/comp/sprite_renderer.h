#pragma once

#include <functional>
#include "../ngn/gfx/texture.h"

struct SpriteRenderer {
	std::reference_wrapper<const ngn::Texture> texture;
	uint8_t hframes;
	uint8_t vframes;
	ngn::real_t currentFrame;
};
