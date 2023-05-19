#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#include <iostream>
#include <memory>
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"

const auto screen = std::make_unique<const Screen>(800, 600, false);
const auto gfx = std::make_unique<Graphics>();

static void update() {
	const auto halfWidth = screen->getWidth() / 2;
	const auto halfHeight = screen->getHeight() / 2;
	gfx->setup2D(0, 0, screen->getWidth(), screen->getHeight());
	gfx->cls(Color::multiply(Color::GREEN, 0.5f));
	gfx->drawRect(32, 32, halfWidth - 32, halfHeight - 32, Color::rgb(255, 255, 128));
	gfx->drawRect(halfWidth, halfHeight, halfWidth - 32, halfHeight - 32, Color::rgb(255, 128, 255));
	screen->refresh();
}

int main() {
	if (!gfx->isValid()) {
		std::cout << gfx->getError() << std::endl;
	}
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(update, 0, true);
#else
	while (screen->isOpened()) {
		update();
	}
#endif
	return 0;
}
