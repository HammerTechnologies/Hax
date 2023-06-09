#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#include <iostream>
#include "core.h"
#include "game.h"

#ifdef EMSCRIPTEN
void update() noexcept {
	Game::getInstance()->update();
}
#endif

int main() noexcept {
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(update, 0, true);
#else
	while (Game::getInstance()->update()) {}
	Game::getInstance()->finish();
	Core::terminate();
#endif
	return 0;
}
