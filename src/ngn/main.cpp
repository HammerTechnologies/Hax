#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#include "core.h"

void init();
bool update();
void finish();

#ifdef EMSCRIPTEN
void emscripten_update() {
	update();
}
#endif

int main() noexcept {
	init();
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(emscripten_update, 0, true);
#else
	while (update()) {}
	finish();
	ngn::Core::terminate();
#endif
	return 0;
}
