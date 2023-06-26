#pragma once

#include <memory>
#include <string>
#include "../ngn/gfx/color.h"
#include "../ngn/gfx/font.h"
#include "../ngn/gfx/graphics.h"
#include "../ngn/mth/vec2.h"

struct TextRenderer {
	std::shared_ptr<ngn::Font> font;
	std::string text;
	ngn::Vec2r position;
	ngn::color_t color;

	void render(const ngn::Graphics& gfx) const noexcept {
		gfx.drawText(font.get(), text, position, color);
	}
};
