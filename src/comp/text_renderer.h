#pragma once

#include <memory>
#include <string>
#include "../ngn/gfx/color.h"
#include "../ngn/gfx/font.h"
#include "../ngn/gfx/graphics.h"
#include "../ngn/mth/vec2.h"

struct TextRenderer {
	std::string text;
	ngn::Vec2r position;
	ngn::color_t color;

	void render(const ngn::Font& font, const ngn::Graphics& gfx) const noexcept {
		gfx.drawText(&font, text, position, color);
	}
};
