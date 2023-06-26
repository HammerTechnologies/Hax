#pragma once

#include <functional>
#include "../ngn/gfx/graphics.h"
#include "../ngn/gfx/screen.h"
#include "../ngn/gfx/viewer.h"
#include "../ngn/io/input.h"

struct GameData {
	std::reference_wrapper<const ngn::Input> input;
	std::reference_wrapper<ngn::Graphics> graphics;
	std::reference_wrapper<ngn::Screen> screen;
	std::reference_wrapper<ngn::Viewer> viewer;
};
