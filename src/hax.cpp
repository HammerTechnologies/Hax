#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#include <memory>
#include "color.h"
#include "graphics.h"
#include "screen.h"

std::unique_ptr<Screen> screen = nullptr;
std::unique_ptr<Graphics> gfx = nullptr;

static void update() {
	gfx->cls(Color::multiply(Color::BLUE, 0.5f));
	screen->refresh();
}

int main() {
	screen = std::make_unique<Screen>(800, 600, false);
	gfx = std::make_unique<Graphics>();
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(update, 0, true);
#else
	while (screen->isOpened()) {
		update();
	}
#endif
	return 0;
}
