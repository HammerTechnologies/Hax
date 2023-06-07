#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef LoadString
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#endif
#ifndef _MSC_VER
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#define _chdir chdir
#else
#include <direct.h>
#endif
#include <memory>
#include <sstream>
#include <string>
#include "graphics/core.h"
#include "graphics/font.h"
#include "graphics/texture.h"
#include "graphics/viewer.h"
#include "maze/generator.h"
#include "logger.h"

struct Hax {
	Hax() noexcept
	: m_core{640, 360, false, m_logger},
		m_viewer{
			Vec3r{0, 0, -5},
			Vec3r{},
			0,
			0,
			m_core.getScreen().getWidth(),
			m_core.getScreen().getHeight()
		},
		m_maze{generateMaze(16, 16, 0)},
		m_font{m_core.getGraphics().loadFont("Minecraft.ttf", 16.0f)},
		m_tex{m_core.getGraphics().loadTexture("mockup.png")},
		m_yaw{0} {}

	void update() noexcept {
		if (m_core.getInput().isKeyDown(Key::ESC)) {
			exit(0);
		}
		std::ostringstream ss;
		ss << m_core.getScreen().getWidth() << "x" << m_core.getScreen().getHeight() << " @ " << m_core.getScreen().getFps() << " FPS";

		m_yaw += M_PI * m_core.getScreen().getDelta();
		m_viewer.m_viewportWidth = m_core.getScreen().getWidth();
		m_viewer.m_viewportHeight = m_core.getScreen().getHeight();

		m_core.getGraphics().setup2D(0, 0, m_core.getScreen().getWidth(), m_core.getScreen().getHeight());
		m_core.getGraphics().cls();
		m_core.getGraphics().drawTexture(*m_tex, 0, 0, m_core.getScreen().getWidth(), m_core.getScreen().getHeight());
		m_core.getGraphics().drawText(*m_font, ss.str(), 14, 12);

		for (uint8_t y = 0; y < m_maze->getHeight(); y++) {
			for (uint8_t x = 0; x < m_maze->getWidth(); x++) {
				drawNode(m_maze->getNodeAt(x, y), x + 2, y + 2, 16, Color::YELLOW);
			}
		}

		m_core.getGraphics().setup3D(m_viewer);
		m_core.getGraphics().drawQuad(
			Mat4r::transform(
				Vec3r{},
				Quatr::fromEuler(Vec3r{0, m_yaw, 0}),
				Vec3r{1, 1, 1}),
			Color::ORANGE);
		m_core.getScreen().refresh();
	}

	bool isScreenOpened() const noexcept {
		return m_core.getScreen().isOpened();
	}
private:
	Logger m_logger;
	Core m_core;
	Viewer m_viewer;
	std::unique_ptr<Graph> m_maze;
	std::unique_ptr<Font> m_font;
	std::unique_ptr<Texture> m_tex;
	real_t m_yaw;

	void drawNode(
		const std::shared_ptr<GraphNode>& gn,
		uint16_t tileX,
		uint16_t tileY,
		uint16_t size,
		uint32_t color) const noexcept {
		const auto half = size / 2;
		const auto& graphics = m_core.getGraphics();
		if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size + half, half, 1, color);
		} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth())	{
			graphics.drawRect(tileX * size + half, tileY * size + half, half, 1, color);
		} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
			graphics.drawRect(tileX * size + half, tileY * size, 1, half, color);
		} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
			graphics.drawRect(tileX * size + half, tileY * size + half, 1, half, color);
		} else if (!gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
		} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && !gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size + half, size, 1, color);
		} else if (!gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
			graphics.drawRect(tileX * size + half, tileY * size, 1, size, color);
		} else if (!gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
			graphics.drawRect(tileX * size + half, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size + half, 1, half, color);
		} else if (gn->hasWest() && !gn->hasEast() && !gn->hasNorth() && gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size + half, 1, half, color);
		} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
			graphics.drawRect(tileX * size + half, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, half, color);
		} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && !gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, half, color);
		} else if (!gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
			graphics.drawRect(tileX * size + half, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, size, color);
		} else if (gn->hasWest() && !gn->hasEast() && gn->hasNorth() && gn->hasSouth())	{
			graphics.drawRect(tileX * size, tileY * size + half, half, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, size, color);
		} else if (gn->hasWest() && gn->hasEast() && !gn->hasNorth() && gn->hasSouth())	{
			graphics.drawRect(tileX * size, tileY * size + half, size, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size + half, 1, half, color);
		} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && !gn->hasSouth())	{
			graphics.drawRect(tileX * size, tileY * size + half, size, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, half, color);
		} else if (gn->hasWest() && gn->hasEast() && gn->hasNorth() && gn->hasSouth()) {
			graphics.drawRect(tileX * size, tileY * size, size, 1, color);
			graphics.drawRect(tileX * size + half, tileY * size, 1, size, color);
		}
	}
};

std::unique_ptr<Hax> g_hax = nullptr;

inline std::string extractDir(const std::string& filename) noexcept {
	size_t find_pos = filename.rfind('\\');
	if (find_pos == std::string::npos) {
		find_pos = filename.rfind('/');
	}
	return filename.substr(0, find_pos);
}

inline std::string exeDir() noexcept {
	char path[FILENAME_MAX];
#if defined(_WIN32)
	path[GetModuleFileNameA(nullptr, path, FILENAME_MAX)] = 0;
#elif defined(__APPLE__)
	uint32_t size = FILENAME_MAX;
	_NSGetExecutablePath(path, &size);
#else
	path[readlink("/proc/self/exe", path, FILENAME_MAX)] = 0;
#endif
	return extractDir(path);
}

inline bool changeDir(const std::string& path) noexcept {
	return _chdir(path.c_str()) == 0;
}

void update() noexcept {
	g_hax->update();
}

int main() noexcept {
	changeDir(exeDir() + "/assets");
	g_hax = std::make_unique<Hax>();

#ifdef EMSCRIPTEN
	emscripten_set_main_loop(update, 0, true);
#else
	while (g_hax->isScreenOpened()) {
		update();
	}
	g_hax = nullptr;
	Core::terminate();
#endif
	return 0;
}
