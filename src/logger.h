#pragma once

#include <iostream>
#include <string>

struct Logger {
	Logger() noexcept {
		info("Logger initialized");
	}

	~Logger() noexcept {
		info("Logger deinitialized");
	}

	void info(const std::string& msg) const noexcept {
		write("INFO", msg);
	}

	void warning(const std::string& msg) const noexcept {
		write("WARN", msg);
	}

	void error(const std::string& msg) const noexcept {
		write("ERR ", msg);
	}
private:
	void write(const std::string& level, const std::string& msg) const noexcept {
		std::cout << level << " :: " << msg << std::endl << std::flush;
	}
};
