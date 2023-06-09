#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#include "core.h"

void init();
bool update();
void finish();

int main() noexcept {
	init();
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(update, 0, true);
#else
	while (update()) {}
	finish();
	Core::terminate();
#endif
	return 0;
}
