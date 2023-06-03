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
#include "logger.h"

struct Hax {
	Hax() noexcept
	: m_core{640, 360, false, m_logger},
		m_font{m_core.getGraphics().loadFont("Minecraft.ttf", 16.0f)},
		m_tex{m_core.getGraphics().loadTexture("mockup.png")} {
		if (!m_font->isValid()) {
			m_logger.error("Could not load font.");
		}
		if (!m_tex->isValid()) {
			m_logger.error("Could not load texture.");
		}
	}

	void update() noexcept {
		if (m_core.getInput().isKeyDown(Key::ESC)) {
			exit(0);
		}
		std::ostringstream ss;
		ss << m_core.getScreen().getWidth() << "x" << m_core.getScreen().getHeight() << " @ " << m_core.getScreen().getFps() << " FPS";

		m_core.getGraphics().setup2D(0, 0, m_core.getScreen().getWidth(), m_core.getScreen().getHeight());
		m_core.getGraphics().cls();
		m_core.getGraphics().drawTexture(*m_tex, 0, 0, m_core.getScreen().getWidth(), m_core.getScreen().getHeight());
		m_core.getGraphics().drawText(*m_font, ss.str(), 14, 12);
		m_core.getScreen().refresh();
	}

	bool isScreenOpened() const noexcept { return m_core.getScreen().isOpened(); }
private:
	Logger m_logger;
	Core m_core;
	std::unique_ptr<Font> m_font;
	std::unique_ptr<Texture> m_tex;
};

std::unique_ptr<Hax> g_hax = nullptr;

inline std::string extractDir(const std::string& filename) noexcept {
	size_t find_pos = filename.rfind('\\');
	if (find_pos == std::string::npos) find_pos = filename.rfind('/');
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
