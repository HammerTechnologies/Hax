#include <array>
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
#include <string>

inline std::string extractDir(const std::string& filename) noexcept {
	auto find_pos = filename.rfind('\\');
	if (find_pos == std::string::npos) {
		find_pos = filename.rfind('/');
	}
	return filename.substr(0, find_pos);
}

inline std::string exeDir() noexcept {
	auto path = std::array<char, FILENAME_MAX> {};
#if defined(_WIN32)
	path[GetModuleFileNameA(nullptr, path.data(), path.size())] = 0;
#elif defined(__APPLE__)
	auto size = uint32_t {path.size()};
	_NSGetExecutablePath(path, &size);
#else
	path[readlink("/proc/self/exe", path.data(), path.size())] = 0;
#endif
	return extractDir(path.data());
}

inline bool changeDir(const std::string& path) noexcept {
	return _chdir(path.c_str()) == 0;
}
