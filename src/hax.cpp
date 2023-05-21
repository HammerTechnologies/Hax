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
#include <iostream>
#include <memory>
#include <string>
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/texture.h"

struct Hax {
	Hax() noexcept
	: m_screen{std::make_unique<const Screen>(800, 600, false)},
		m_gfx{std::make_unique<Graphics>()},
		m_tex{std::make_unique<Texture>("smile.png")},
		m_angle{0} {
		if (!m_gfx->isValid()) {
			std::cout << m_gfx->getError() << std::endl;
		}
		if (!m_tex->isValid()) {
			std::cout << "Could not load texture" << std::endl;
		}
	}

	void update() noexcept {
		++m_angle;
		const auto halfWidth = m_screen->getWidth() / 2;
		const auto halfHeight = m_screen->getHeight() / 2;
		m_gfx->setup2D(0, 0, m_screen->getWidth(), m_screen->getHeight());
		m_gfx->cls(Color::multiply(Color::GREEN, static_cast<real_t>(0.5)));
		m_gfx->drawRect(32, 32, halfWidth - 32, halfHeight - 32, Color::rgb(255, 255, 128));
		m_gfx->drawRect(halfWidth, halfHeight, halfWidth - 32, halfHeight - 32, Color::rgb(255, 128, 255));
		m_gfx->drawTexture(*m_tex, halfWidth - m_tex->getWidth() / 2, halfHeight - m_tex->getHeight() / 2, 0, 0, m_angle);
		m_screen->refresh();
	}

	bool isScreenOpened() const noexcept { return m_screen->isOpened(); }
private:
	const std::unique_ptr<const Screen> m_screen;
	const std::unique_ptr<Graphics> m_gfx;
	const std::unique_ptr<Texture> m_tex;
	real_t m_angle;
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
	path[GetModuleFileNameA(NULL, path, FILENAME_MAX)] = 0;
#elif defined(__APPLE__)
	unsigned int size = FILENAME_MAX;
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
	changeDir(exeDir());
	g_hax = std::make_unique<Hax>();
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(update, 0, true);
#else
	while (g_hax->isScreenOpened()) {
		update();
	}
#endif
	return 0;
}
