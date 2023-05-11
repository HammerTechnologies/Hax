#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#include <memory>
#include "screen.h"

std::unique_ptr<Screen> screen = nullptr;

static void update() {
	screen->refresh();
}

int main() {
	screen = std::make_unique<Screen>(800, 600, false);
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(update, 0, true);
#else
	while (screen->isOpened()) {
		update();
	}
#endif
	return 0;
}
