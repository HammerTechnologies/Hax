#include <glad/glad.h>
#include "graphics.h"

void Graphics::setup2D(int x, int y, int w, int h) noexcept {
	glEnable(GL_SCISSOR_TEST);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CW);
	glViewport(x, y, w, h);
	glScissor(x, y, w, h);
}

void Graphics::cls(uint32_t color) noexcept {
	glClearColor(Color::redf(color), Color::greenf(color), Color::bluef(color), Color::alphaf(color));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
