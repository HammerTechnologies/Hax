#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#include <iostream>
#include "core.h"
#include "game.h"

#ifdef EMSCRIPTEN
void update() noexcept {
	ngn::Game::instance()->update();
}
#endif

int main() noexcept {
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(update, 0, true);
#else
	while (ngn::Game::instance()->update()) {}
	ngn::Game::instance()->finish();
	ngn::Core::terminate();
#endif
	return 0;
}
